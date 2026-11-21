// Stage encode: LLVM values and instructions to camada terms. i1 values are
// Bool terms; every other integer is a bitvector of its width.
#pragma once
#include <camada/camada.h>
#include <llvm/ADT/DenseMap.h>
#include <llvm/IR/Instruction.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>
#include <stdexcept>
#include <string>

namespace vereda::encode {

// IR the encoder cannot handle yet. The walker turns it into UNKNOWN.
struct Unsupported : std::runtime_error {
  using std::runtime_error::runtime_error;
};

class Encoder {
public:
  explicit Encoder(camada::SMTSolver &solver) : s(solver) {}
  camada::SMTSolver &solver() { return s; }

  camada::SMTSortRef sort(llvm::Type *ty);
  // The term bound to v, or a constant. Undef and poison are a fresh value per use.
  camada::SMTExprRef value(const llvm::Value *v);
  void bind(const llvm::Value *v, camada::SMTExprRef term) { env[v] = std::move(term); }
  // A fresh unconstrained term of v's type, named after its origin (nondet calls, arguments).
  camada::SMTExprRef fresh(llvm::Type *ty, const std::string &name);
  // Encodes arithmetic, comparison, cast, select and freeze, binding the result.
  void encode(llvm::Instruction &inst);
  // v != 0 as a Bool term, for assume and assert arguments and branch conditions.
  camada::SMTExprRef isTrue(const llvm::Value *v);

private:
  camada::SMTExprRef toBool(camada::SMTExprRef bv);
  camada::SMTExprRef fromBool(camada::SMTExprRef b, unsigned width);

  camada::SMTSolver &s;
  llvm::DenseMap<const llvm::Value *, camada::SMTExprRef> env;
  unsigned freshCount = 0;
};

std::string describe(const llvm::Value *v);

} // namespace vereda::encode
