// Stage solver: camada glue. Owns the solver choice and decides the checks.
#pragma once
#include "checks/checks.h"
#include <camada/camada.h>
#include <llvm/Support/Error.h>
#include <string>

namespace vereda::solver {

// "bitwuzla", "z3" or "cvc5", subject to what camada was built with.
llvm::Expected<camada::SMTSolverRef> create(const std::string &name);

struct Verdict {
  enum Kind { Safe, Violated, Unknown } kind;
  const checks::Check *check = nullptr; // the violated check, for Violated
  std::string detail;                   // reason, for Unknown
  unsigned checked = 0;                 // checks decided before stopping
};

// Asks the solver about each check in order under its own assumption and
// stops at the first satisfiable one, whose model stays available.
Verdict decide(camada::SMTSolver &s, const checks::Checks &checks);

} // namespace vereda::solver
