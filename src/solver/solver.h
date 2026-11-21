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
};

// Asks the solver about each check under its own assumption; the first
// satisfiable one is the verdict.
Verdict decide(camada::SMTSolver &s, const checks::Checks &checks);

} // namespace vereda::solver
