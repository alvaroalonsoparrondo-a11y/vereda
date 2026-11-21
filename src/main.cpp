// Smoke driver: parse an LLVM IR file, list its defined functions, and run one
// query through camada. It proves the two dependencies link; the walker
// replaces it.
#include <camada/camada.h>
#include <camada/camadafeatures.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IRReader/IRReader.h>
#include <llvm/Support/SourceMgr.h>
#include <llvm/Support/raw_ostream.h>

int main(int argc, char **argv) {
  if (argc != 2) {
    llvm::errs() << "usage: " << argv[0] << " <file.ll|file.bc>\n";
    return 2;
  }
  llvm::LLVMContext ctx;
  llvm::SMDiagnostic err;
  std::unique_ptr<llvm::Module> module = llvm::parseIRFile(argv[1], err, ctx);
  if (!module) {
    err.print(argv[0], llvm::errs());
    return 1;
  }
  for (const llvm::Function &f : *module)
    if (!f.isDeclaration())
      llvm::outs() << f.getName() << "\n";

#if CAMADA_HAVE_BITWUZLA
  camada::SMTSolverRef solver = camada::createBitwuzlaSolver();
#elif CAMADA_HAVE_Z3
  camada::SMTSolverRef solver = camada::createZ3Solver();
#else
#error "camada was built without Bitwuzla or Z3"
#endif
  camada::SMTExprRef x = solver->mkSymbol("x", solver->mkBVSort(32));
  solver->addConstraint(solver->mkEqual(x, solver->mkBVFromDec(7, 32)));
  bool sat = solver->check() == camada::CheckResult::SAT;
  llvm::outs() << "solver: " << (sat ? "sat" : "unsat") << "\n";
  return sat ? 0 : 1;
}
