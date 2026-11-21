// Stage walker: the trace, one step per source-level event in walk order.
// The witness stage reads it back under the solver's model.
#pragma once
#include "ir/debug.h"
#include <camada/camada.h>
#include <string>
#include <vector>

namespace vereda::walker {

struct Step {
  enum Kind { Assignment, Assumption } kind;
  camada::SMTExprRef guard; // path condition at the step
  ir::SourceLoc loc;
  std::string text;         // the variable, or the assumed expression
  camada::SMTExprRef value; // assignments only
  bool isUnsigned = false;  // from the debug type; bitvectors carry no sign
};

using Trace = std::vector<Step>;

} // namespace vereda::walker
