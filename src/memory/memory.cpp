#include "memory/memory.h"

#include "util/unsupported.h"
#include <llvm/IR/GlobalVariable.h>

using namespace llvm;
using camada::SMTExprRef;
using camada::SMTSortRef;
using vereda::Unsupported;

namespace vereda::memory {

static const unsigned ObjBits = 32;
static const int64_t IntProvenance = -1; // a byte that holds no pointer

Memory::Memory(camada::SMTSolver &s, const DataLayout &dl)
    : s(s), dl(dl), ptrBits(dl.getPointerSizeInBits(0)) {
  if (dl.isBigEndian())
    throw Unsupported("big-endian targets");
  bases = s.mkSymbol("bases", s.mkArraySort(s.mkBVSort(ObjBits), s.mkBVSort(ptrBits)));
  objects.push_back({s.mkBVFromDec(0, ptrBits), s.mkBVFromDec(0, ptrBits)});
  s.addConstraint(s.mkEqual(base(s.mkBVFromDec(0, ObjBits)), objects[0].base));
  end = s.mkBVFromDec(1, ptrBits); // no object at address 0
}

SMTSortRef Memory::pointerSort() { return s.mkBVSort(ObjBits + ptrBits); }
SMTExprRef Memory::ptr(SMTExprRef obj, SMTExprRef off) { return s.mkBVConcat(obj, off); }
SMTExprRef Memory::null() { return s.mkBVFromDec(0, ObjBits + ptrBits); }
SMTExprRef Memory::object(SMTExprRef p) {
  return s.mkBVExtract(ObjBits + ptrBits - 1, ptrBits, p);
}
SMTExprRef Memory::offset(SMTExprRef p) { return s.mkBVExtract(ptrBits - 1, 0, p); }
SMTExprRef Memory::advance(SMTExprRef p, SMTExprRef delta) {
  return ptr(object(p), s.mkBVAdd(offset(p), delta));
}
SMTExprRef Memory::bytePtr(SMTExprRef p, uint64_t i) {
  return i ? advance(p, s.mkBVFromDec(i, ptrBits)) : p;
}
SMTExprRef Memory::base(SMTExprRef obj) { return s.mkArraySelect(bases, obj); }

SMTExprRef Memory::fits(SMTExprRef size) {
  // ponytail: several objects near PTRDIFF_MAX on one path cannot all be
  // laid out, which ends that path; a real allocator would return null.
  return s.mkBVUle(size, s.mkBVLshr(s.mkBVNot(s.mkBVFromDec(0, ptrBits)),
                                    s.mkBVFromDec(1, ptrBits)));
}

SMTExprRef Memory::allocate(SMTExprRef size, uint64_t align, SMTExprRef exists) {
  unsigned id = objects.size();
  SMTExprRef b = s.mkSymbol("base#" + std::to_string(id), s.mkBVSort(ptrBits));
  SMTExprRef e = s.mkBVAdd(b, size);
  // Ordered with a gap, aligned, not wrapping: objects never overlap, and a
  // one-past-the-end address belongs to its own object only. These bind
  // only where the object exists, or a size on one path would remove
  // inputs from every path.
  SMTExprRef layout = s.mkAnd(s.mkBVUgt(b, end), s.mkNot(s.mkBVUAddOverflow(b, size)));
  if (align > 1)
    layout = s.mkAnd(layout, s.mkEqual(s.mkBVAnd(b, s.mkBVFromDec(align - 1, ptrBits)),
                                       s.mkBVFromDec(0, ptrBits)));
  s.addConstraint(s.mkImplies(exists, layout));
  SMTExprRef obj = s.mkBVFromDec(id, ObjBits);
  s.addConstraint(s.mkEqual(base(obj), b));
  objects.push_back({b, size});
  end = s.mkIte(exists, e, end); // an object not allocated takes no space
  return ptr(obj, s.mkBVFromDec(0, ptrBits));
}

void Memory::allocateGlobals(const Module &m) {
  for (const GlobalVariable &g : m.globals()) {
    uint64_t size = dl.getTypeAllocSize(g.getValueType());
    globals[&g] = allocate(s.mkBVFromDec(size, ptrBits), g.getPointerAlignment(dl).value(),
                           s.mkBool(true));
  }
}

SMTExprRef Memory::global(const GlobalValue *g) const {
  auto it = globals.find(g);
  if (it == globals.end())
    throw Unsupported("address of " + g->getName().str());
  return it->second;
}

SMTExprRef Memory::address(SMTExprRef p) { return s.mkBVAdd(base(object(p)), offset(p)); }

SMTExprRef Memory::fromAddress(SMTExprRef a) {
  // The object whose range holds a, or null with offset a.
  // ponytail: one comparison per object created so far; the static
  // points-to analysis will narrow this.
  SMTExprRef r = ptr(s.mkBVFromDec(0, ObjBits), a);
  for (unsigned id = 1; id < objects.size(); ++id) {
    const Object &o = objects[id];
    // One past the end still belongs to the object: the gap keeps it unique.
    SMTExprRef inside = s.mkAnd(s.mkBVUge(a, o.base), s.mkBVUle(a, s.mkBVAdd(o.base, o.size)));
    r = s.mkIte(inside, ptr(s.mkBVFromDec(id, ObjBits), s.mkBVSub(a, o.base)), r);
  }
  return r;
}

State Memory::initial() {
  SMTSortRef index = pointerSort();
  std::string n = std::to_string(fresh++);
  return {s.mkSymbol("memory#" + n, s.mkArraySort(index, s.mkBVSort(8))),
          s.mkSymbol("provenance#" + n, s.mkArraySort(index, s.mkBVSort(ObjBits)))};
}

State Memory::ite(SMTExprRef c, const State &a, const State &b) {
  return {s.mkIte(c, a.data, b.data), s.mkIte(c, a.prov, b.prov)};
}

// Bits in memory order: byte i of the store is bits [8i+7, 8i].
void Memory::storeBytes(State &st, SMTExprRef p, SMTExprRef bits, SMTExprRef prov) {
  unsigned n = bits->getWidth() / 8;
  for (unsigned i = 0; i < n; ++i) {
    SMTExprRef at = bytePtr(p, i);
    st.data = s.mkArrayStore(st.data, at, s.mkBVExtract(8 * i + 7, 8 * i, bits));
    st.prov = s.mkArrayStore(st.prov, at, prov);
  }
}

static unsigned storeBits(const DataLayout &dl, Type *ty) {
  return 8 * dl.getTypeStoreSize(ty).getFixedValue();
}

void Memory::store(State &st, SMTExprRef p, SMTExprRef v, Type *ty) {
  unsigned bits = storeBits(dl, ty);
  if (ty->isPointerTy()) {
    storeBytes(st, p, address(v), object(v));
    return;
  }
  if (!ty->isIntegerTy())
    throw Unsupported("store of a non-integer value");
  if (ty->isIntegerTy(1))
    v = s.mkIte(v, s.mkBVFromDec(1, 8), s.mkBVFromDec(0, 8));
  else if (v->getWidth() < bits)
    v = s.mkBVZeroExt(v, bits - v->getWidth());
  storeBytes(st, p, v, s.mkBVFromDec(IntProvenance, ObjBits));
}

SMTExprRef Memory::load(const State &st, SMTExprRef p, Type *ty) {
  if (!ty->isIntegerTy() && !ty->isPointerTy())
    throw Unsupported("load of a non-integer value");
  unsigned n = storeBits(dl, ty) / 8;
  SMTExprRef bits = s.mkArraySelect(st.data, p);
  for (unsigned i = 1; i < n; ++i)
    bits = s.mkBVConcat(s.mkArraySelect(st.data, bytePtr(p, i)), bits);
  if (ty->isPointerTy()) {
    // ponytail: the provenance of the first byte stands for the pointer.
    SMTExprRef obj = s.mkArraySelect(st.prov, p);
    SMTExprRef isInt = s.mkEqual(obj, s.mkBVFromDec(IntProvenance, ObjBits));
    return s.mkIte(isInt, fromAddress(bits), ptr(obj, s.mkBVSub(bits, base(obj))));
  }
  if (ty->isIntegerTy(1))
    return s.mkEqual(s.mkBVExtract(0, 0, bits), s.mkBVFromDec(1, 1));
  unsigned width = ty->getIntegerBitWidth();
  return width < bits->getWidth() ? s.mkBVExtract(width - 1, 0, bits) : bits;
}

// ponytail: one array store per byte, so a large zeroed global or memset is
// a long store chain. A range store or a constant base would fix it.
void Memory::set(State &st, SMTExprRef p, SMTExprRef byte, uint64_t n) {
  SMTExprRef prov = s.mkBVFromDec(IntProvenance, ObjBits);
  for (uint64_t i = 0; i < n; ++i) {
    SMTExprRef at = bytePtr(p, i);
    st.data = s.mkArrayStore(st.data, at, byte);
    st.prov = s.mkArrayStore(st.prov, at, prov);
  }
}

void Memory::copy(State &st, SMTExprRef dst, SMTExprRef src, uint64_t n) {
  // Read everything first, so overlapping ranges copy as memmove does.
  std::vector<std::pair<SMTExprRef, SMTExprRef>> bytes;
  for (uint64_t i = 0; i < n; ++i) {
    SMTExprRef at = bytePtr(src, i);
    bytes.push_back({s.mkArraySelect(st.data, at), s.mkArraySelect(st.prov, at)});
  }
  for (uint64_t i = 0; i < n; ++i) {
    SMTExprRef at = bytePtr(dst, i);
    st.data = s.mkArrayStore(st.data, at, bytes[i].first);
    st.prov = s.mkArrayStore(st.prov, at, bytes[i].second);
  }
}

void Memory::initialise(State &st, const Module &m,
                        const std::function<SMTExprRef(const Constant *)> &valueOf) {
  for (const GlobalVariable &g : m.globals()) {
    if (!g.hasInitializer()) // extern: contents unknown
      continue;
    const Constant *init = g.getInitializer();
    // Static storage zeroes padding, which storeConstant does not write.
    if (hasPadding(init->getType()) && !init->isNullValue())
      set(st, globals.lookup(&g), s.mkBVFromDec(0, 8),
          dl.getTypeAllocSize(init->getType()).getFixedValue());
    storeConstant(st, globals.lookup(&g), init, valueOf);
  }
}

bool Memory::hasPadding(Type *ty) const {
  if (auto *st_ = dyn_cast<StructType>(ty))
    return dl.getStructLayout(st_)->hasPadding() ||
           llvm::any_of(st_->elements(), [this](Type *e) { return hasPadding(e); });
  if (auto *at = dyn_cast<ArrayType>(ty))
    return hasPadding(at->getElementType()) ||
           dl.getTypeAllocSize(at->getElementType()) != dl.getTypeStoreSize(at->getElementType());
  return false;
}

void Memory::storeConstant(State &st, SMTExprRef p, const Constant *c,
                           const std::function<SMTExprRef(const Constant *)> &valueOf) {
  Type *ty = c->getType();
  if (isa<UndefValue>(c)) // also poison: leave the contents nondet
    return;
  if (c->isNullValue()) {
    set(st, p, s.mkBVFromDec(0, 8), dl.getTypeStoreSize(ty).getFixedValue());
    return;
  }
  if (ty->isIntegerTy() || ty->isPointerTy()) {
    store(st, p, valueOf(c), ty);
    return;
  }
  if (auto *st_ = dyn_cast<StructType>(ty)) {
    const StructLayout *layout = dl.getStructLayout(st_);
    for (unsigned i = 0; i < st_->getNumElements(); ++i)
      storeConstant(st, bytePtr(p, layout->getElementOffset(i)), c->getAggregateElement(i),
                    valueOf);
    return;
  }
  if (auto *at = dyn_cast<ArrayType>(ty)) {
    uint64_t stride = dl.getTypeAllocSize(at->getElementType());
    for (uint64_t i = 0; i < at->getNumElements(); ++i)
      storeConstant(st, bytePtr(p, i * stride), c->getAggregateElement(i), valueOf);
    return;
  }
  throw Unsupported("global initialiser of this type");
}

} // namespace vereda::memory
