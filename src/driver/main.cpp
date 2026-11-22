// Stage driver: parses options, runs the stages, prints the verdict.
#include "checks/checks.h"
#include "encode/encoder.h"
#include "ir/load.h"
#include "solver/solver.h"
#include "util/log.h"
#include "walker/walker.h"
#include "witness/counterexample.h"

#include <llvm/Config/llvm-config.h>
#include <llvm/Support/CommandLine.h>
#include <llvm/Support/WithColor.h>
#include <llvm/Support/raw_ostream.h>

using namespace llvm;
using vereda::util::progress;

static cl::opt<std::string> inputFile(cl::Positional, cl::desc("<file.bc|file.ll>"),
                                      cl::Required);
static cl::opt<bool> dumpIROnly("dump-ir-only", cl::desc("Print the IR after the pass list and exit"));
static cl::opt<bool> dumpIRToo("dump-ir-too", cl::desc("Print the IR after the pass list, then verify"));
static cl::opt<bool> dumpSMTOnly("dump-smt-only",
                                 cl::desc("Print the formula as SMT-LIB after the walk and exit; "
                                          "it is satisfiable exactly when some check fails"));
static cl::opt<bool> dumpSMTToo("dump-smt-too",
                                cl::desc("Print the formula as SMT-LIB after the walk, then solve"));
static cl::opt<std::string> entry("entry", cl::desc("Entry function"), cl::init("main"));
static cl::opt<unsigned> unwind("unwind",
                                cl::desc("Loop iterations and recursion depth (default: "
                                         "unroll until the next iteration is unreachable)"),
                                cl::init(0));
static cl::opt<bool> noUnwindingAssertions(
    "no-unwinding-assertions", cl::desc("Assume the unwinding bound instead of checking it"));
static cl::opt<bool> forceMallocSuccess("force-malloc-success",
                                        cl::desc("malloc never returns null"));
static cl::opt<bool> incrementalBMC(
    "incremental-bmc",
    cl::desc("Check bounds 1, 2, ... until the verdict does not depend on the bound"));
static cl::opt<unsigned> maxKStep("max-k-step", cl::desc("Largest bound for --incremental-bmc"),
                                  cl::init(50));
static cl::opt<std::string> solverName("solver", cl::desc("SMT solver: bitwuzla, z3, cvc5"),
                                       cl::init("bitwuzla"));

static void printVersion(raw_ostream &os) {
  os << "Vereda " VEREDA_VERSION " (LLVM " LLVM_VERSION_STRING ", camada " VEREDA_CAMADA_VERSION
        ")\n";
}

static int unknown(const Twine &reason) {
  outs() << "\nVERIFICATION UNKNOWN: " << reason << "\n";
  return 2;
}

// What bmc() returns under --incremental-bmc when a loop or recursion needs
// a larger bound.
static const int BoundTooSmall = -1;

// Walks fn with the given bound, solves and prints the verdict; returns the
// exit code. Under --incremental-bmc, a failed unwinding or recursion
// assertion is not a verdict but BoundTooSmall; an unknown from the solver
// still ends the run, as in ESBMC.
static int bmc(Function &fn, unsigned bound) {
  Expected<camada::SMTSolverRef> created = vereda::solver::create(solverName);
  if (!created) {
    errs() << "vereda: " << toString(created.takeError()) << "\n";
    return 1;
  }
  camada::SMTSolver &solver = **created;
  progress("Walking " + entry);
  vereda::util::Stopwatch walkTime;
  vereda::encode::Terms terms(solver);
  std::unique_ptr<vereda::memory::Memory> memory;
  try {
    memory = std::make_unique<vereda::memory::Memory>(terms, fn.getParent()->getDataLayout());
  } catch (const vereda::Unsupported &e) {
    return unknown(Twine("unsupported: ") + e.what());
  }
  vereda::encode::Encoder enc(terms, *memory);
  vereda::checks::Checks checks;
  vereda::walker::Trace trace;
  vereda::walker::Options walkOpts{bound, !noUnwindingAssertions, forceMallocSuccess};
  if (Error e = vereda::walker::walk(fn, walkOpts, enc, *memory, checks, trace))
    return unknown(toString(std::move(e)));
  // Peak memory after the walk covers the walker and the terms it built;
  // the growth during solving is the solver's search.
  outs() << "Walk time: " << walkTime.elapsed() << " (" << checks.size() << " checks, "
         << enc.symbolCount() << " symbols, peak memory " << vereda::util::peakMemory()
         << ")\n";
  outs().flush(); // solving may run until a timeout kills the process

  if (dumpSMTOnly || dumpSMTToo) {
    // The checks are assumptions in decide(); here their disjunction is
    // asserted, in a scope of its own, so the script stands alone.
    camada::SMTExprRef anyViolated = terms.boolean(false);
    for (const vereda::checks::Check &c : checks)
      anyViolated = terms.lor(anyViolated, c.violated);
    solver.push();
    solver.addConstraint(anyViolated);
    std::string formula;
    solver.dump(formula);
    solver.pop();
    outs() << formula;
    if (dumpSMTOnly)
      return 0;
  }

  progress("Solving with " + solver.getSolverNameAndVersion());
  vereda::util::Stopwatch solveTime;
  vereda::solver::Verdict verdict = vereda::solver::decide(solver, checks);
  outs() << "Solving time: " << solveTime.elapsed() << " (peak memory "
         << vereda::util::peakMemory() << ")\n";

  if (verdict.kind == vereda::solver::Verdict::Unknown)
    return unknown(verdict.detail);

  if (incrementalBMC && verdict.check &&
      verdict.check->property != vereda::checks::Property::Assertion) {
    outs() << "Bound " << bound << " too small: " << verdict.check->comment << "\n";
    return BoundTooSmall;
  }

  if (verdict.check) {
    progress("Building error trace");
    vereda::witness::printCounterexample(solver, trace, checks,
                                         verdict.check - checks.data(), outs());
  }
  if (!checks.empty()) {
    outs() << "\n** Results:\n";
    std::string lastUnit;
    for (unsigned i = 0; i < verdict.checked; ++i) {
      const vereda::checks::Check &c = checks[i];
      std::string unit = c.loc.file + ", function " + c.loc.function;
      if (unit != lastUnit)
        outs() << (lastUnit.empty() ? "" : "\n") << unit << "\n";
      lastUnit = unit;
      outs() << (&c == verdict.check ? "  FAILED       [" : "  SUCCESS      [") << c.id()
             << "]  line " << c.loc.line << "  " << c.comment << "\n";
    }
    outs() << "\n** " << (verdict.check ? 1 : 0) << " of " << verdict.checked
           << " properties failed\n";
  }
  outs() << "\n";
  if (verdict.check) {
    WithColor(outs(), raw_ostream::RED, /*Bold=*/true) << "VERIFICATION FAILED";
    outs() << "\n";
    return 1;
  }
  WithColor(outs(), raw_ostream::GREEN, /*Bold=*/true) << "VERIFICATION SUCCESSFUL";
  outs() << "\n";
  return 0;
}

int main(int argc, char **argv) {
  cl::SetVersionPrinter(printVersion);
  cl::ParseCommandLineOptions(argc, argv, "Vereda: LLVM-IR verifier\n");

  progress("Loading " + inputFile);
  vereda::util::Stopwatch loadTime;
  LLVMContext ctx;
  Expected<std::unique_ptr<Module>> module = vereda::ir::load(inputFile, ctx);
  if (!module) {
    errs() << argv[0] << ": " << toString(module.takeError()) << "\n";
    return 1;
  }
  outs() << "Target: " << (*module)->getDataLayout().getPointerSizeInBits() << "-bit "
         << ((*module)->getDataLayout().isLittleEndian() ? "little" : "big") << "-endian "
         << (*module)->getTargetTriple().str() << "\n";
  outs() << "IR preparation time: " << loadTime.elapsed() << "\n";
  if (dumpIROnly || dumpIRToo) {
    (*module)->print(outs(), nullptr);
    if (dumpIROnly)
      return 0;
  }
  Function *fn = (*module)->getFunction(entry);
  if (!fn || fn->isDeclaration()) {
    errs() << argv[0] << ": no function " << entry << "\n";
    return 1;
  }

  if (!incrementalBMC) {
    if (maxKStep.getNumOccurrences()) {
      errs() << argv[0] << ": --max-k-step needs --incremental-bmc\n";
      return 1;
    }
    return bmc(*fn, unwind);
  }
  if (dumpSMTOnly) {
    errs() << argv[0] << ": --dump-smt-only stops before the solver picks the bound; use --unwind\n";
    return 1;
  }
  if (unwind || noUnwindingAssertions) {
    errs() << argv[0] << ": --incremental-bmc chooses the bound and checks it\n";
    return 1;
  }
  for (unsigned k = 1; k <= maxKStep; ++k) {
    // A new walk and solver per bound, as ESBMC: the walk merges the paths
    // leaving a loop, so a larger bound changes everything after it. (One
    // solver with a scope per bound was measured and not kept; see
    // docs/spike-survey.md.)
    progress("Checking bound k = " + std::to_string(k));
    if (int r = bmc(*fn, k); r != BoundTooSmall)
      return r;
  }
  return unknown("no verdict up to bound " + std::to_string(maxKStep));
}
