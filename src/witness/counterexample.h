// Stage witness: the counterexample, read from the solver's model.
#pragma once
#include "checks/checks.h"
#include "walker/trace.h"
#include <camada/camada.h>
#include <llvm/Support/raw_ostream.h>

namespace vereda::witness {

// Prints the steps the model reaches with their values, then the violated
// check as the final state, in ESBMC's layout. The solver must hold the
// model from the check that found the violation.
void printCounterexample(camada::SMTSolver &s, const walker::Trace &trace,
                         const checks::Check &violated, llvm::raw_ostream &os);

} // namespace vereda::witness
