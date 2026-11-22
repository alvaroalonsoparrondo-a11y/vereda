// Stage encode: LLVM values and instructions to camada terms. i1 values are
// Bool terms; every other integer is a bitvector of its width. A struct of
// integers is one bitvector with its fields packed from the low bits up.
// Pointers are the memory stage's (object, offset) bitvectors.
#pragma once
#include "memory/memory.h"
#include "util/unsupported.h"
#include <camada/camada.h>
#include <llvm/ADT/APInt.h>
#include <llvm/ADT/DenseMap.h>
#include <llvm/IR/InstrTypes.h>
#include <llvm/IR/Instruction.h>
#include <llvm/IR/Operator.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>
#include <string>

namespace vereda::encode {

using vereda::Unsupported;

class Encoder {
public:
  Encoder(camada::SMTSolver &solver, memory::Memory &mem) : s(solver), mem(mem) {}
  camada::SMTSolver &solver() { return s; }
  unsigned symbolCount() const { return freshCount; }

  camada::SMTSortRef sort(llvm::Type *ty);
  // The term bound to v, or a constant. Undef and poison are a fresh value per use.
  camada::SMTExprRef value(const llvm::Value *v);
  void bind(const llvm::Value *v, camada::SMTExprRef term) { env[v] = std::move(term); }
  // The term bound to v, or a null term.
  camada::SMTExprRef bound(const llvm::Value *v) const { return env.lookup(v); }
  // A fresh unconstrained term of v's type, named after its origin (nondet calls, arguments).
  camada::SMTExprRef fresh(llvm::Type *ty, const std::string &name);
  // Encodes arithmetic, comparison, cast, select, freeze, extractvalue and
  // getelementptr, binding the result.
  void encode(llvm::Instruction &inst);
  // Encodes the arithmetic intrinsics (llvm.*.with.overflow), binding the
  // result. Returns false for any other intrinsic.
  bool intrinsic(llvm::CallBase &c);
  // v != 0 as a Bool term, for assume and assert arguments and branch conditions.
  camada::SMTExprRef isTrue(const llvm::Value *v);
  // An integer term (Bool for i1) as a bitvector of width bits, extending by
  // sign or zero, or truncating.
  camada::SMTExprRef resize(camada::SMTExprRef v, unsigned width, bool isSigned);

private:
  camada::SMTExprRef toBool(camada::SMTExprRef bv);
  camada::SMTExprRef fromBool(camada::SMTExprRef b, unsigned width);
  camada::SMTExprRef constant(const llvm::APInt &v);
  camada::SMTExprRef binary(unsigned opcode, const llvm::Value *lhs, const llvm::Value *rhs);
  camada::SMTExprRef castTo(unsigned opcode, const llvm::Value *op, llvm::Type *dst);
  camada::SMTExprRef gep(const llvm::GEPOperator &g);

  camada::SMTSolver &s;
  memory::Memory &mem;
  llvm::DenseMap<const llvm::Value *, camada::SMTExprRef> env;
  unsigned freshCount = 0;
};

std::string describe(const llvm::Value *v);

} // namespace vereda::encode
