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

Verdict decide(camada::SMTSolver &s, const checks::Checks &checks, bool all,
               function_ref<void(const checks::Check &)> violated) {
  // Assertions first, then unwinding assertions, as ESBMC's incremental BMC:
  // a bug within the bound is reported even where a loop is not unwound.
  Verdict v;
  v.status.assign(checks.size(), Status::NotChecked);
  for (bool unwinding : {false, true})
    for (size_t i = 0; i < checks.size(); ++i) {
      const checks::Check &check = checks[i];
      if ((check.property != checks::Property::Assertion) != unwinding)
        continue;
      switch (s.checkSatAssuming({check.violated})) {
      case camada::CheckResult::SAT:
        v.status[i] = Status::Fails;
        if (!v.check) {
          v.kind = Verdict::Violated;
          v.check = &check;
        }
        violated(check);
        if (!all)
          return v;
        break;
      case camada::CheckResult::UNSAT:
        v.status[i] = Status::Holds;
        break;
      case camada::CheckResult::UNKNOWN:
        if (v.check) // a violation found stands
          return v;
        return {Verdict::Unknown, &check, "solver answered unknown: " + s.reasonUnknownDetail(),
                std::move(v.status)};
      }
    }
  return v;
}

} // namespace vereda::solver
