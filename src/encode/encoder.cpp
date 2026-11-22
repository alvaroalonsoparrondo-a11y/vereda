#include "encode/encoder.h"

#include <llvm/IR/Constants.h>
#include <llvm/IR/GlobalVariable.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/InstrTypes.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/Intrinsics.h>
#include <llvm/Support/raw_ostream.h>

using namespace llvm;
using camada::SMTExprRef;
using camada::SMTSortRef;

namespace vereda::encode {

std::string describe(const Value *v) {
  std::string str;
  raw_string_ostream os(str);
  v->print(os);
  return str;
}

static std::string describe(const Type *ty) {
  std::string str;
  raw_string_ostream os(str);
  ty->print(os);
  return str;
}

// Width of an integer, or of a struct of integers packed into one bitvector;
// 0 for anything else.
static unsigned packedWidth(Type *ty) {
  if (ty->isIntegerTy())
    return ty->getIntegerBitWidth();
  auto *st = dyn_cast<StructType>(ty);
  if (!st)
    return 0;
  unsigned width = 0;
  for (Type *field : st->elements()) {
    if (!field->isIntegerTy())
      return 0;
    width += field->getIntegerBitWidth();
  }
  return width;
}

SMTSortRef Encoder::sort(Type *ty) {
  if (ty->isIntegerTy(1))
    return s.mkBoolSort();
  if (ty->isPointerTy())
    return mem.pointerSort();
  if (unsigned width = packedWidth(ty))
    return s.mkBVSort(width);
  throw Unsupported("type " + describe(ty));
}

SMTExprRef Encoder::fresh(Type *ty, const std::string &name) {
  return t.symbol(name + "#" + std::to_string(freshCount++), sort(ty));
}

SMTExprRef Encoder::value(const Value *v) {
  if (auto it = env.find(v); it != env.end())
    return it->second;
  if (auto *ci = dyn_cast<ConstantInt>(v))
    return ci->getBitWidth() == 1 ? t.boolean(ci->isOne()) : t.bv(ci->getValue());
  if (isa<UndefValue>(v)) // also poison
    return fresh(v->getType(), "undef");
  if (isa<ConstantPointerNull>(v))
    return mem.null();
  if (auto *g = dyn_cast<GlobalVariable>(v))
    return mem.global(g);
  if (auto *ce = dyn_cast<ConstantExpr>(v)) {
    if (auto *g = dyn_cast<GEPOperator>(ce))
      return gep(*g);
    if (ce->isCast())
      return castTo(ce->getOpcode(), ce->getOperand(0), ce->getType());
    if (Instruction::isBinaryOp(ce->getOpcode()))
      return binary(ce->getOpcode(), ce->getOperand(0), ce->getOperand(1));
  }
  if (auto *f = dyn_cast<Function>(v))
    return mem.global(f);
  throw Unsupported("value " + describe(v));
}

SMTExprRef Encoder::resize(SMTExprRef v, unsigned width, bool isSigned) {
  if (v->isBoolSort())
    v = fromBool(v, 1);
  unsigned from = v->getWidth();
  if (from < width)
    return isSigned ? t.sext(v, width - from) : t.zext(v, width - from);
  return from > width ? t.extract(v, width - 1, 0) : v;
}

SMTExprRef Encoder::gep(const GEPOperator &g) {
  unsigned bits = mem.pointerBits();
  APInt offset(bits, 0);
  SmallMapVector<Value *, APInt, 4> variable;
  if (g.getType()->isVectorTy() ||
      !g.collectOffset(mem.layout(), bits, variable, offset))
    throw Unsupported("getelementptr " + describe(&g));
  SMTExprRef delta = t.bv(offset);
  for (auto &[index, scale] : variable)
    delta = t.add(delta, t.mul(resize(value(index), bits, true), t.bv(scale)));
  return mem.advance(value(g.getPointerOperand()), delta);
}

SMTExprRef Encoder::castTo(unsigned opcode, const Value *op, Type *dst) {
  Type *src = op->getType();
  SMTExprRef a = value(op);
  switch (opcode) {
  case Instruction::PtrToInt:
    return dst->isIntegerTy(1) ? toBool(resize(mem.address(a), 1, false))
                               : resize(mem.address(a), dst->getIntegerBitWidth(), false);
  case Instruction::IntToPtr:
    return mem.fromAddress(resize(a, mem.pointerBits(), false));
  case Instruction::BitCast:
    if (src->isPointerTy() && dst->isPointerTy())
      return a;
    break;
  default:
    break;
  }
  if (!src->isIntegerTy() || !dst->isIntegerTy())
    throw Unsupported("cast " + std::string(Instruction::getOpcodeName(opcode)) + " from " +
                      describe(op));
  unsigned from = src->getIntegerBitWidth(), to = dst->getIntegerBitWidth();
  switch (opcode) {
  case Instruction::ZExt:
    return from == 1 ? fromBool(a, to) : t.zext(a, to - from);
  case Instruction::SExt:
    return from == 1 ? t.ite(a, t.bvnot(t.bv(0, to)), t.bv(0, to))
                     : t.sext(a, to - from);
  case Instruction::Trunc: {
    SMTExprRef r = t.extract(a, to - 1, 0);
    return to == 1 ? t.eq(r, t.bv(1, 1)) : r;
  }
  default:
    throw Unsupported("cast " + std::string(Instruction::getOpcodeName(opcode)));
  }
}

SMTExprRef Encoder::toBool(SMTExprRef bv) {
  return t.lnot(t.eq(bv, t.bv(0, bv->getWidth())));
}

SMTExprRef Encoder::fromBool(SMTExprRef b, unsigned width) {
  return t.ite(b, t.bv(1, width), t.bv(0, width));
}

SMTExprRef Encoder::isTrue(const Value *v) {
  SMTExprRef t = value(v);
  return v->getType()->isIntegerTy(1) ? t : toBool(t);
}

SMTExprRef Encoder::binary(unsigned opcode, const Value *lhs, const Value *rhs) {
  bool isBool = lhs->getType()->isIntegerTy(1);
  SMTExprRef a = value(lhs), b = value(rhs);
  switch (opcode) {
  case Instruction::And: return isBool ? t.land(a, b) : t.bvand(a, b);
  case Instruction::Or:  return isBool ? t.lor(a, b) : t.bvor(a, b);
  case Instruction::Xor: return isBool ? t.lxor(a, b) : t.bvxor(a, b);
  default: break;
  }
  if (isBool) { // arithmetic on i1: compute in BV1
    a = fromBool(a, 1);
    b = fromBool(b, 1);
  }
  SMTExprRef r;
  switch (opcode) {
  case Instruction::Add:  r = t.add(a, b); break;
  case Instruction::Sub:  r = t.sub(a, b); break;
  case Instruction::Mul:  r = t.mul(a, b); break;
  case Instruction::UDiv: r = t.udiv(a, b); break;
  case Instruction::SDiv: r = t.sdiv(a, b); break;
  case Instruction::URem: r = t.urem(a, b); break;
  case Instruction::SRem: r = t.srem(a, b); break;
  case Instruction::Shl:  r = t.shl(a, b); break;
  case Instruction::LShr: r = t.lshr(a, b); break;
  case Instruction::AShr: r = t.ashr(a, b); break;
  default: throw Unsupported(std::string("instruction ") + Instruction::getOpcodeName(opcode));
  }
  return isBool ? toBool(r) : r;
}

void Encoder::encode(Instruction &inst) {
  SMTExprRef r;
  if (isa<BinaryOperator>(inst)) {
    r = binary(inst.getOpcode(), inst.getOperand(0), inst.getOperand(1));
  } else if (auto *cmp = dyn_cast<ICmpInst>(&inst)) {
    SMTExprRef a = value(cmp->getOperand(0)), b = value(cmp->getOperand(1));
    // Pointers are equal when object and offset are; ordered comparison
    // compares addresses.
    if (cmp->getOperand(0)->getType()->isPointerTy() && !cmp->isEquality()) {
      a = mem.address(a);
      b = mem.address(b);
    }
    bool isBool = cmp->getOperand(0)->getType()->isIntegerTy(1);
    if (isBool && !cmp->isEquality()) {
      a = fromBool(a, 1);
      b = fromBool(b, 1);
    }
    switch (cmp->getPredicate()) {
    case CmpInst::ICMP_EQ:  r = t.eq(a, b); break;
    case CmpInst::ICMP_NE:  r = t.lnot(t.eq(a, b)); break;
    case CmpInst::ICMP_UGT: r = t.ugt(a, b); break;
    case CmpInst::ICMP_UGE: r = t.uge(a, b); break;
    case CmpInst::ICMP_ULT: r = t.ult(a, b); break;
    case CmpInst::ICMP_ULE: r = t.ule(a, b); break;
    case CmpInst::ICMP_SGT: r = t.sgt(a, b); break;
    case CmpInst::ICMP_SGE: r = t.sge(a, b); break;
    case CmpInst::ICMP_SLT: r = t.slt(a, b); break;
    case CmpInst::ICMP_SLE: r = t.sle(a, b); break;
    default: throw Unsupported("predicate " + std::string(cmp->getPredicateName(cmp->getPredicate())));
    }
  } else if (auto *sel = dyn_cast<SelectInst>(&inst)) {
    r = t.ite(value(sel->getCondition()), value(sel->getTrueValue()),
                value(sel->getFalseValue()));
  } else if (auto *c = dyn_cast<CastInst>(&inst)) {
    r = castTo(c->getOpcode(), c->getOperand(0), c->getDestTy());
  } else if (auto *g = dyn_cast<GetElementPtrInst>(&inst)) {
    r = gep(*llvm::cast<GEPOperator>(g));
  } else if (isa<FreezeInst>(inst)) {
    r = value(inst.getOperand(0));
  } else if (auto *ev = dyn_cast<ExtractValueInst>(&inst)) {
    auto *st = dyn_cast<StructType>(ev->getAggregateOperand()->getType());
    if (!st || !packedWidth(st) || ev->getNumIndices() != 1)
      throw Unsupported("extractvalue " + describe(&inst));
    unsigned field = ev->getIndices()[0], low = 0;
    for (unsigned i = 0; i < field; ++i)
      low += st->getElementType(i)->getIntegerBitWidth();
    unsigned width = st->getElementType(field)->getIntegerBitWidth();
    r = t.extract(value(ev->getAggregateOperand()), low + width - 1, low);
    if (width == 1)
      r = t.eq(r, t.bv(1, 1));
  } else {
    throw Unsupported(std::string("instruction ") + inst.getOpcodeName());
  }
  bind(&inst, r);
}

bool Encoder::intrinsic(CallBase &c) {
  Function *f = c.getCalledFunction();
  SMTExprRef (Terms::*op)(const SMTExprRef &, const SMTExprRef &) = nullptr;
  SMTExprRef (Terms::*overflow)(const SMTExprRef &, const SMTExprRef &) = nullptr;
  switch (f->getIntrinsicID()) {
  case Intrinsic::sadd_with_overflow: op = &Terms::add; overflow = &Terms::saddo; break;
  case Intrinsic::uadd_with_overflow: op = &Terms::add; overflow = &Terms::uaddo; break;
  case Intrinsic::ssub_with_overflow: op = &Terms::sub; overflow = &Terms::ssubo; break;
  case Intrinsic::usub_with_overflow: op = &Terms::sub; overflow = &Terms::usubo; break;
  case Intrinsic::smul_with_overflow: op = &Terms::mul; overflow = &Terms::smulo; break;
  case Intrinsic::umul_with_overflow: op = &Terms::mul; overflow = &Terms::umulo; break;
  default: return false;
  }
  SMTExprRef a = value(c.getArgOperand(0)), b = value(c.getArgOperand(1));
  // {result, overflow bit}: the overflow bit packs above the result.
  bind(&c, t.concat(fromBool((t.*overflow)(a, b), 1), (t.*op)(a, b)));
  return true;
}

} // namespace vereda::encode
