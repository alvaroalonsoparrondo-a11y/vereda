// Stage driver: parses options, runs the stages, prints the verdict.
#include "checks/checks.h"
#include "encode/encoder.h"
#include "ir/load.h"
#include "solver/solver.h"
#include "walker/walker.h"

#include <llvm/Support/CommandLine.h>
#include <llvm/Support/raw_ostream.h>

using namespace llvm;

static cl::opt<std::string> inputFile(cl::Positional, cl::desc("<file.bc|file.ll>"),
                                      cl::Required);
static cl::opt<bool> dumpIR("dump-ir", cl::desc("Print the IR after the pass list and exit"));
static cl::opt<std::string> entry("entry", cl::desc("Entry function"), cl::init("main"));
static cl::opt<std::string> solverName("solver", cl::desc("SMT solver: bitwuzla, z3, cvc5"),
                                       cl::init("bitwuzla"));

static int unknown(const Twine &reason) {
  outs() << "VERIFICATION UNKNOWN: " << reason << "\n";
  return 2;
}

int main(int argc, char **argv) {
  cl::ParseCommandLineOptions(argc, argv, "vereda: LLVM-IR verifier\n");
  LLVMContext ctx;
  Expected<std::unique_ptr<Module>> module = vereda::ir::load(inputFile, ctx);
  if (!module) {
    errs() << argv[0] << ": " << toString(module.takeError()) << "\n";
    return 1;
  }
  if (dumpIR) {
    (*module)->print(outs(), nullptr);
    return 0;
  }
  Function *fn = (*module)->getFunction(entry);
  if (!fn || fn->isDeclaration()) {
    errs() << argv[0] << ": no function " << entry << "\n";
    return 1;
  }

  Expected<camada::SMTSolverRef> solver = vereda::solver::create(solverName);
  if (!solver) {
    errs() << argv[0] << ": " << toString(solver.takeError()) << "\n";
    return 1;
  }
  vereda::encode::Encoder enc(**solver);
  vereda::checks::Checks checks;
  if (Error e = vereda::walker::walk(*fn, enc, checks))
    return unknown(toString(std::move(e)));

  vereda::solver::Verdict verdict = vereda::solver::decide(**solver, checks);
  switch (verdict.kind) {
  case vereda::solver::Verdict::Safe:
    outs() << "VERIFICATION SUCCESSFUL\n";
    return 0;
  case vereda::solver::Verdict::Violated:
    outs() << "Violated property:\n  " << verdict.check->location << "\n  "
           << verdict.check->what << "\n\nVERIFICATION FAILED\n";
    return 1;
  case vereda::solver::Verdict::Unknown:
    return unknown(verdict.detail);
  }
}
