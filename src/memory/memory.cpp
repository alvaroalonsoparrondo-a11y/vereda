#include "memory/memory.h"

#include "util/unsupported.h"
#include <llvm/IR/GlobalVariable.h>
#include <set>

using namespace llvm;
using camada::SMTExprRef;
using camada::SMTSortRef;
using vereda::Unsupported;

namespace vereda::memory {

static const unsigned ObjBits = 32;
static const int64_t IntProvenance = -1; // a byte that holds no pointer

Memory::Memory(encode::Terms &t, const DataLayout &dl)
    : t(t), s(t.solver()), dl(dl), ptrBits(dl.getPointerSizeInBits(0)) {
  if (dl.isBigEndian())
    throw Unsupported("big-endian targets");
  bases = t.symbol("bases", s.mkArraySort(s.mkBVSort(ObjBits), s.mkBVSort(ptrBits)));
  objects.push_back({t.bv(0, ptrBits), t.bv(0, ptrBits)});
  s.addConstraint(t.eq(base(t.bv(0, ObjBits)), objects[0].base));
  end = t.bv(1, ptrBits); // no object at address 0
}

SMTSortRef Memory::pointerSort() { return s.mkBVSort(ObjBits + ptrBits); }
SMTExprRef Memory::ptr(SMTExprRef obj, SMTExprRef off) { return t.concat(obj, off); }
SMTExprRef Memory::null() { return t.bv(0, ObjBits + ptrBits); }
SMTExprRef Memory::object(SMTExprRef p) {
  return t.extract(p, ObjBits + ptrBits - 1, ptrBits);
}
SMTExprRef Memory::offset(SMTExprRef p) { return t.extract(p, ptrBits - 1, 0); }
SMTExprRef Memory::advance(SMTExprRef p, SMTExprRef delta) {
  return ptr(object(p), t.add(offset(p), delta));
}
SMTExprRef Memory::bytePtr(SMTExprRef p, uint64_t i) {
  return i ? advance(p, t.bv(i, ptrBits)) : p;
}
SMTExprRef Memory::base(SMTExprRef obj) {
  SMTExprRef c, x, y;
  if (t.split(obj, c, x, y))
    return t.ite(c, base(x), base(y));
  if (const APInt *id = t.constant(obj); id && id->ult(objects.size()))
    return objects[id->getZExtValue()].base;
  return t.select(bases, obj);
}

SMTExprRef Memory::fits(SMTExprRef size) {
  // Several objects near PTRDIFF_MAX on one path cannot all be
  // laid out, which ends that path; a real allocator would return null.
  return t.ule(size, t.lshr(t.bvnot(t.bv(0, ptrBits)),
                                    t.bv(1, ptrBits)));
}

SMTExprRef Memory::allocate(SMTExprRef size, uint64_t align, SMTExprRef exists) {
  unsigned id = objects.size();
  SMTExprRef b = t.symbol("base#" + std::to_string(id), s.mkBVSort(ptrBits));
  SMTExprRef e = t.add(b, size);
  // Ordered with a gap, aligned, not wrapping: objects never overlap, and a
  // one-past-the-end address belongs to its own object only. These bind
  // only where the object exists, or a size on one path would remove
  // inputs from every path.
  SMTExprRef layout = t.land(t.ugt(b, end), t.lnot(t.uaddo(b, size)));
  if (align > 1)
    layout = t.land(layout, t.eq(t.bvand(b, t.bv(align - 1, ptrBits)),
                                       t.bv(0, ptrBits)));
  s.addConstraint(t.implies(exists, layout));
  SMTExprRef obj = t.bv(id, ObjBits);
  s.addConstraint(t.eq(base(obj), b));
  objects.push_back({b, size});
  end = t.ite(exists, e, end); // an object not allocated takes no space
  return ptr(obj, t.bv(0, ptrBits));
}

void Memory::allocateGlobals(const Module &m) {
  for (const GlobalVariable &g : m.globals()) {
    uint64_t size = dl.getTypeAllocSize(g.getValueType());
    globals[&g] = allocate(t.bv(size, ptrBits), g.getPointerAlignment(dl).value(),
                           t.boolean(true));
  }
}

SMTExprRef Memory::global(const GlobalValue *g) const {
  auto it = globals.find(g);
  if (it == globals.end())
    throw Unsupported("address of " + g->getName().str());
  return it->second;
}

SMTExprRef Memory::address(SMTExprRef p) { return t.add(base(object(p)), offset(p)); }

SMTExprRef Memory::fromAddress(SMTExprRef a) {
  // The object whose range holds a, or null with offset a.
  // One comparison per object created so far; the static
  // points-to analysis will narrow this.
  SMTExprRef r = ptr(t.bv(0, ObjBits), a);
  for (unsigned id = 1; id < objects.size(); ++id) {
    const Object &o = objects[id];
    // One past the end still belongs to the object: the gap keeps it unique.
    SMTExprRef inside = t.land(t.uge(a, o.base), t.ule(a, t.add(o.base, o.size)));
    r = t.ite(inside, ptr(t.bv(id, ObjBits), t.sub(a, o.base)), r);
  }
  return r;
}

State Memory::initial() {
  SMTSortRef index = pointerSort();
  std::string n = std::to_string(fresh++);
  return {t.symbol("memory#" + n, s.mkArraySort(index, s.mkBVSort(8))),
          t.symbol("provenance#" + n, s.mkArraySort(index, s.mkBVSort(ObjBits)))};
}

// Past this many known bytes in a state, all go to the arrays,
// which bounds the copy on write; a persistent map would lift it.
static const size_t MaxKnown = 4096;

std::optional<Memory::Key> Memory::key(SMTExprRef p) const {
  const APInt *v = t.constant(p);
  if (!v)
    return std::nullopt;
  return Key{v->extractBitsAsZExtValue(ObjBits, ptrBits), v->extractBitsAsZExtValue(ptrBits, 0)};
}

SMTExprRef Memory::ptr(const Key &k) {
  return ptr(t.bv(k.first, ObjBits), t.bv(k.second, ptrBits));
}

State::Known &Memory::own(State &st) {
  if (!st.known)
    st.known = std::make_shared<State::Known>();
  else if (st.known.use_count() > 1)
    st.known = std::make_shared<State::Known>(*st.known);
  return *st.known;
}

void Memory::flush(State &st, std::optional<uint64_t> object) {
  if (!st.known)
    return;
  // Keys sort by object first, so one object's bytes are one range.
  auto range = [&] {
    auto &k = *st.known;
    return object ? std::make_pair(k.lower_bound({*object, 0}), k.lower_bound({*object + 1, 0}))
                  : std::make_pair(k.begin(), k.end());
  };
  auto [lo, hi] = range();
  if (lo == hi)
    return;
  if (st.known.use_count() > 1) {
    own(st);
    std::tie(lo, hi) = range();
  }
  for (auto it = lo; it != hi; ++it) {
    SMTExprRef at = ptr(it->first);
    st.data = t.store(st.data, at, it->second.data);
    st.prov = t.store(st.prov, at, it->second.prov);
  }
  st.known->erase(lo, hi);
}

void Memory::prepare(State &st, SMTExprRef p) {
  SMTExprRef c, x, y;
  if (key(p) || t.split(p, c, x, y))
    return;
  const APInt *obj = t.constant(object(p));
  flush(st, obj ? std::optional<uint64_t>(obj->getZExtValue()) : std::nullopt);
}

int Memory::side(const SMTExprRef &c) {
  if (!context)
    return -1;
  if (t.entails(context, c))
    return 1;
  return t.entails(context, t.lnot(c)) ? 0 : -1;
}

State::Cell Memory::readByte(const State &st, SMTExprRef at) {
  SMTExprRef c, x, y;
  if (t.split(at, c, x, y)) { // one of two constant pointers
    if (int pick = side(c); pick >= 0)
      return readByte(st, pick ? x : y);
    State::Cell a = readByte(st, x), b = readByte(st, y);
    return {t.ite(c, a.data, b.data), t.ite(c, a.prov, b.prov)};
  }
  if (std::optional<Key> k = key(at); k && st.known)
    if (auto it = st.known->find(*k); it != st.known->end())
      return it->second;
  return {t.select(st.data, at), t.select(st.prov, at)};
}

void Memory::writeByte(State &st, SMTExprRef at, const State::Cell &c) {
  SMTExprRef cond, x, y;
  if (t.split(at, cond, x, y)) { // each side keeps its old byte unless chosen
    if (int pick = side(cond); pick >= 0) {
      writeByte(st, pick ? x : y, c);
      return;
    }
    State::Cell a = readByte(st, x), b = readByte(st, y);
    writeByte(st, x, {t.ite(cond, c.data, a.data), t.ite(cond, c.prov, a.prov)});
    writeByte(st, y, {t.ite(cond, b.data, c.data), t.ite(cond, b.prov, c.prov)});
    return;
  }
  std::optional<Key> k = key(at);
  if (!k) {
    st.data = t.store(st.data, at, c.data);
    st.prov = t.store(st.prov, at, c.prov);
    return;
  }
  own(st)[*k] = c;
  if (st.known->size() > MaxKnown)
    flush(st);
}

State Memory::ite(SMTExprRef c, const State &a0, const State &b0) {
  if (a0.known == b0.known)
    return {t.ite(c, a0.data, b0.data), t.ite(c, a0.prov, b0.prov), a0.known};
  // An object whose bytes would become a choice between two values that
  // multiply or divide goes to the arrays on both sides instead. There the
  // solver bit-blasts a stored value only where a read needs it; as a choice,
  // all of them up front (RERS Problem14 ran out of memory).
  State a = a0, b = b0;
  std::map<Key, std::pair<State::Cell, State::Cell>> sides;
  std::set<uint64_t> moved;
  for (const State *st : {&a, &b})
    if (st->known)
      for (const auto &e : *st->known) {
        auto [it, added] = sides.try_emplace(e.first);
        if (!added)
          continue;
        // A byte known on one side only reads the other side's arrays,
        // which the flushes below change only at other objects.
        it->second = {readByte(a, ptr(e.first)), readByte(b, ptr(e.first))};
        const SMTExprRef &x = it->second.first.data, &y = it->second.second.data;
        if (x.get() != y.get() && (t.arithmetic(x) || t.arithmetic(y)))
          moved.insert(e.first.first);
      }
  for (uint64_t object : moved) {
    flush(a, object);
    flush(b, object);
  }
  auto known = std::make_shared<State::Known>();
  for (const auto &[key, xy] : sides)
    if (!moved.count(key.first))
      known->emplace(key, State::Cell{t.ite(c, xy.first.data, xy.second.data),
                                      t.ite(c, xy.first.prov, xy.second.prov)});
  State r{t.ite(c, a.data, b.data), t.ite(c, a.prov, b.prov), std::move(known)};
  if (r.known->size() > MaxKnown)
    flush(r);
  return r;
}

// Bits in memory order: byte i of the store is bits [8i+7, 8i].
void Memory::storeBytes(State &st, SMTExprRef p, SMTExprRef bits, SMTExprRef prov) {
  prepare(st, p);
  unsigned n = bits->getWidth() / 8;
  for (unsigned i = 0; i < n; ++i)
    writeByte(st, bytePtr(p, i), {t.extract(bits, 8 * i + 7, 8 * i), prov});
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
    v = t.ite(v, t.bv(1, 8), t.bv(0, 8));
  else if (v->getWidth() < bits)
    v = t.zext(v, bits - v->getWidth());
  storeBytes(st, p, v, t.bv(IntProvenance, ObjBits));
}

SMTExprRef Memory::load(State &st, SMTExprRef p, Type *ty) {
  if (!ty->isIntegerTy() && !ty->isPointerTy())
    throw Unsupported("load of a non-integer value");
  prepare(st, p);
  unsigned n = storeBits(dl, ty) / 8;
  State::Cell first = readByte(st, p);
  SMTExprRef bits = first.data;
  for (unsigned i = 1; i < n; ++i)
    bits = t.concat(readByte(st, bytePtr(p, i)).data, bits);
  if (ty->isPointerTy()) {
    // The provenance of the first byte stands for the pointer.
    SMTExprRef obj = first.prov;
    SMTExprRef isInt = t.eq(obj, t.bv(IntProvenance, ObjBits));
    return t.ite(isInt, fromAddress(bits), ptr(obj, t.sub(bits, base(obj))));
  }
  if (ty->isIntegerTy(1))
    return t.eq(t.extract(bits, 0, 0), t.bv(1, 1));
  unsigned width = ty->getIntegerBitWidth();
  return width < bits->getWidth() ? t.extract(bits, width - 1, 0) : bits;
}

// One array store per byte, so a large zeroed global or memset is
// a long store chain. A range store or a constant base would fix it.
void Memory::set(State &st, SMTExprRef p, SMTExprRef byte, uint64_t n) {
  prepare(st, p);
  SMTExprRef prov = t.bv(IntProvenance, ObjBits);
  for (uint64_t i = 0; i < n; ++i)
    writeByte(st, bytePtr(p, i), {byte, prov});
}

void Memory::copy(State &st, SMTExprRef dst, SMTExprRef src, uint64_t n) {
  // Read everything first, so overlapping ranges copy as memmove does.
  prepare(st, src);
  prepare(st, dst);
  std::vector<State::Cell> bytes;
  for (uint64_t i = 0; i < n; ++i)
    bytes.push_back(readByte(st, bytePtr(src, i)));
  for (uint64_t i = 0; i < n; ++i)
    writeByte(st, bytePtr(dst, i), bytes[i]);
}

void Memory::initialise(State &st, const Module &m,
                        const std::function<SMTExprRef(const Constant *)> &valueOf) {
  for (const GlobalVariable &g : m.globals()) {
    if (!g.hasInitializer()) // extern: contents unknown
      continue;
    const Constant *init = g.getInitializer();
    // Static storage zeroes padding, which storeConstant does not write.
    if (hasPadding(init->getType()) && !init->isNullValue())
      set(st, globals.lookup(&g), t.bv(0, 8),
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
    set(st, p, t.bv(0, 8), dl.getTypeStoreSize(ty).getFixedValue());
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
