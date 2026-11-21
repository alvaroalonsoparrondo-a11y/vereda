// Stage checks: property checks collected during the walk. Each is a term
// that is satisfiable only if the property is violated, tagged with its
// property and source location so one walk can serve several properties.
#pragma once
#include "ir/debug.h"
#include <camada/camada.h>
#include <string>
#include <vector>

namespace vereda::checks {

enum class Property { Reachability };

struct Check {
  Property property;
  ir::SourceLoc loc;
  std::string comment; // the callee, e.g. "__VERIFIER_assert"
  std::string expr;    // the asserted expression's source text, if any
  unsigned index;      // per function, from 1
  camada::SMTExprRef violated;

  // ESBMC's property id, e.g. "main.assertion.1".
  std::string id() const { return loc.function + ".assertion." + std::to_string(index); }
};

using Checks = std::vector<Check>;

} // namespace vereda::checks
