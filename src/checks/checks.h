// Stage checks: property checks collected during the walk. Each is a term
// that is satisfiable only if the property is violated, tagged with its
// property and source location so one walk can serve several properties.
#pragma once
#include <camada/camada.h>
#include <string>
#include <vector>

namespace vereda::checks {

enum class Property { Reachability };

struct Check {
  Property property;
  std::string location; // file:line:col
  std::string what;     // e.g. "reach_error is reachable"
  camada::SMTExprRef violated;
};

using Checks = std::vector<Check>;

} // namespace vereda::checks
