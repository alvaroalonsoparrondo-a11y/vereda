#include "solver/solver.h"

#include <camada/camadafeatures.h>

using namespace llvm;

namespace vereda::solver {

Expected<camada::SMTSolverRef> create(const std::string &name) {
#if CAMADA_HAVE_BITWUZLA
  if (name == "bitwuzla")
    return camada::createBitwuzlaSolver();
#endif
#if CAMADA_HAVE_Z3
  if (name == "z3")
    return camada::createZ3Solver();
#endif
#if CAMADA_HAVE_CVC5
  if (name == "cvc5")
    return camada::createCVC5Solver();
#endif
  return createStringError(inconvertibleErrorCode(), "solver %s is not available",
                           name.c_str());
}

Verdict decide(camada::SMTSolver &s, const checks::Checks &checks) {
  // Assertions first, then unwinding assertions, as ESBMC's incremental BMC:
  // a bug within the bound is reported even where a loop is not unwound.
  unsigned checked = 0;
  for (bool unwinding : {false, true})
    for (const checks::Check &check : checks) {
      if ((check.property != checks::Property::Assertion) != unwinding)
        continue;
      ++checked;
      switch (s.checkSatAssuming({check.violated})) {
      case camada::CheckResult::SAT:
        return {Verdict::Violated, &check, "", checked};
      case camada::CheckResult::UNSAT:
        break;
      case camada::CheckResult::UNKNOWN:
        return {Verdict::Unknown, &check, "solver answered unknown: " + s.reasonUnknownDetail(),
                checked};
      }
    }
  return {Verdict::Safe, nullptr, "", checked};
}

} // namespace vereda::solver
