#include "encode/encoder.h"

#include <llvm/ADT/SmallString.h>
#include <llvm/IR/Constants.h>
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
  if (unsigned width = packedWidth(ty))
    return s.mkBVSort(width);
  throw Unsupported("type " + describe(ty));
}

SMTExprRef Encoder::fresh(Type *ty, const std::string &name) {
  return s.mkSymbol(name + "#" + std::to_string(freshCount++), sort(ty));
}

SMTExprRef Encoder::value(const Value *v) {
  if (auto it = env.find(v); it != env.end())
    return it->second;
  if (auto *ci = dyn_cast<ConstantInt>(v)) {
    unsigned width = ci->getBitWidth();
    if (width == 1)
      return s.mkBool(ci->isOne());
    SmallString<128> bits;
    ci->getValue().toString(bits, 2, /*Signed=*/false);
    std::string padded(width - bits.size(), '0');
    padded += bits;
    return s.mkBVFromBin(padded, width);
  }
  if (isa<UndefValue>(v)) // also poison
    return fresh(v->getType(), "undef");
  throw Unsupported("value " + describe(v));
}

SMTExprRef Encoder::toBool(SMTExprRef bv) {
  return s.mkNot(s.mkEqual(bv, s.mkBVFromDec(0, bv->getWidth())));
}

SMTExprRef Encoder::fromBool(SMTExprRef b, unsigned width) {
  return s.mkIte(b, s.mkBVFromDec(1, width), s.mkBVFromDec(0, width));
}

SMTExprRef Encoder::isTrue(const Value *v) {
  SMTExprRef t = value(v);
  return v->getType()->isIntegerTy(1) ? t : toBool(t);
}

void Encoder::encode(Instruction &inst) {
  SMTExprRef r;
  if (auto *bo = dyn_cast<BinaryOperator>(&inst)) {
    bool isBool = inst.getType()->isIntegerTy(1);
    SMTExprRef a = value(bo->getOperand(0)), b = value(bo->getOperand(1));
    switch (bo->getOpcode()) {
    case Instruction::And: r = isBool ? s.mkAnd(a, b) : s.mkBVAnd(a, b); break;
    case Instruction::Or:  r = isBool ? s.mkOr(a, b) : s.mkBVOr(a, b); break;
    case Instruction::Xor: r = isBool ? s.mkXor(a, b) : s.mkBVXor(a, b); break;
    default: {
      if (isBool) { // arithmetic on i1: compute in BV1
        a = fromBool(a, 1);
        b = fromBool(b, 1);
      }
      switch (bo->getOpcode()) {
      case Instruction::Add:  r = s.mkBVAdd(a, b); break;
      case Instruction::Sub:  r = s.mkBVSub(a, b); break;
      case Instruction::Mul:  r = s.mkBVMul(a, b); break;
      case Instruction::UDiv: r = s.mkBVUDiv(a, b); break;
      case Instruction::SDiv: r = s.mkBVSDiv(a, b); break;
      case Instruction::URem: r = s.mkBVURem(a, b); break;
      case Instruction::SRem: r = s.mkBVSRem(a, b); break;
      case Instruction::Shl:  r = s.mkBVShl(a, b); break;
      case Instruction::LShr: r = s.mkBVLshr(a, b); break;
      case Instruction::AShr: r = s.mkBVAshr(a, b); break;
      default: throw Unsupported(std::string("instruction ") + inst.getOpcodeName());
      }
      if (isBool)
        r = toBool(r);
    }
    }
  } else if (auto *cmp = dyn_cast<ICmpInst>(&inst)) {
    SMTExprRef a = value(cmp->getOperand(0)), b = value(cmp->getOperand(1));
    bool isBool = cmp->getOperand(0)->getType()->isIntegerTy(1);
    if (isBool && !cmp->isEquality()) {
      a = fromBool(a, 1);
      b = fromBool(b, 1);
    }
    switch (cmp->getPredicate()) {
    case CmpInst::ICMP_EQ:  r = s.mkEqual(a, b); break;
    case CmpInst::ICMP_NE:  r = s.mkNot(s.mkEqual(a, b)); break;
    case CmpInst::ICMP_UGT: r = s.mkBVUgt(a, b); break;
    case CmpInst::ICMP_UGE: r = s.mkBVUge(a, b); break;
    case CmpInst::ICMP_ULT: r = s.mkBVUlt(a, b); break;
    case CmpInst::ICMP_ULE: r = s.mkBVUle(a, b); break;
    case CmpInst::ICMP_SGT: r = s.mkBVSgt(a, b); break;
    case CmpInst::ICMP_SGE: r = s.mkBVSge(a, b); break;
    case CmpInst::ICMP_SLT: r = s.mkBVSlt(a, b); break;
    case CmpInst::ICMP_SLE: r = s.mkBVSle(a, b); break;
    default: throw Unsupported("predicate " + std::string(cmp->getPredicateName(cmp->getPredicate())));
    }
  } else if (auto *sel = dyn_cast<SelectInst>(&inst)) {
    r = s.mkIte(value(sel->getCondition()), value(sel->getTrueValue()),
                value(sel->getFalseValue()));
  } else if (auto *cast = dyn_cast<CastInst>(&inst)) {
    Type *src = cast->getSrcTy(), *dst = cast->getDestTy();
    if (!src->isIntegerTy() || !dst->isIntegerTy())
      throw Unsupported("cast " + describe(&inst));
    unsigned from = src->getIntegerBitWidth(), to = dst->getIntegerBitWidth();
    SMTExprRef a = value(cast->getOperand(0));
    switch (cast->getOpcode()) {
    case Instruction::ZExt:
      r = from == 1 ? fromBool(a, to) : s.mkBVZeroExt(a, to - from);
      break;
    case Instruction::SExt:
      r = from == 1 ? s.mkIte(a, s.mkBVNot(s.mkBVFromDec(0, to)), s.mkBVFromDec(0, to))
                    : s.mkBVSignExt(a, to - from);
      break;
    case Instruction::Trunc:
      r = s.mkBVExtract(to - 1, 0, a);
      if (to == 1)
        r = s.mkEqual(r, s.mkBVFromDec(1, 1));
      break;
    default: throw Unsupported("cast " + describe(&inst));
    }
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
    r = s.mkBVExtract(low + width - 1, low, value(ev->getAggregateOperand()));
    if (width == 1)
      r = s.mkEqual(r, s.mkBVFromDec(1, 1));
  } else {
    throw Unsupported(std::string("instruction ") + inst.getOpcodeName());
  }
  bind(&inst, r);
}

bool Encoder::intrinsic(CallBase &c) {
  Function *f = c.getCalledFunction();
  SMTExprRef (camada::SMTSolver::*op)(const SMTExprRef &, const SMTExprRef &) = nullptr;
  SMTExprRef (camada::SMTSolver::*overflow)(const SMTExprRef &, const SMTExprRef &) = nullptr;
  switch (f->getIntrinsicID()) {
  case Intrinsic::sadd_with_overflow: op = &camada::SMTSolver::mkBVAdd; overflow = &camada::SMTSolver::mkBVSAddOverflow; break;
  case Intrinsic::uadd_with_overflow: op = &camada::SMTSolver::mkBVAdd; overflow = &camada::SMTSolver::mkBVUAddOverflow; break;
  case Intrinsic::ssub_with_overflow: op = &camada::SMTSolver::mkBVSub; overflow = &camada::SMTSolver::mkBVSSubOverflow; break;
  case Intrinsic::usub_with_overflow: op = &camada::SMTSolver::mkBVSub; overflow = &camada::SMTSolver::mkBVUSubOverflow; break;
  case Intrinsic::smul_with_overflow: op = &camada::SMTSolver::mkBVMul; overflow = &camada::SMTSolver::mkBVSMulOverflow; break;
  case Intrinsic::umul_with_overflow: op = &camada::SMTSolver::mkBVMul; overflow = &camada::SMTSolver::mkBVUMulOverflow; break;
  default: return false;
  }
  SMTExprRef a = value(c.getArgOperand(0)), b = value(c.getArgOperand(1));
  // {result, overflow bit}: the overflow bit packs above the result.
  bind(&c, s.mkBVConcat(fromBool((s.*overflow)(a, b), 1), (s.*op)(a, b)));
  return true;
}

} // namespace vereda::encode
