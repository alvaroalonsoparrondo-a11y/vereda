// Stage witness: the counterexample, read from the solver's model.
#pragma once
#include "walker/trace.h"
#include <camada/camada.h>
#include <llvm/Support/raw_ostream.h>

namespace vereda::witness {

// Prints the steps the model reaches, with their values. The solver must
// hold a model from the check that found the violation.
void printCounterexample(camada::SMTSolver &s, const walker::Trace &trace,
                         llvm::raw_ostream &os);

} // namespace vereda::witness
