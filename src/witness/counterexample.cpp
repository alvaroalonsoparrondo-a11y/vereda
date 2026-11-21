#include "witness/counterexample.h"

using namespace llvm;

namespace vereda::witness {

static std::string valueOf(camada::SMTSolver &s, const walker::Step &step) {
  if (step.value->isBoolSort()) {
    auto b = s.getBool(step.value);
    return b ? (b.value() ? "true" : "false") : "?";
  }
  if (step.value->getWidth() > 64) {
    auto bits = s.getBVInBin(step.value);
    return bits ? "0b" + bits.value() : "?";
  }
  if (step.isUnsigned) {
    auto v = s.getBVUnsigned(step.value);
    return v ? std::to_string(v.value()) : "?";
  }
  auto v = s.getBV(step.value);
  return v ? std::to_string(v.value()) : "?";
}

void printCounterexample(camada::SMTSolver &s, const walker::Trace &trace, raw_ostream &os) {
  os << "Counterexample:\n";
  unsigned n = 0;
  for (const walker::Step &step : trace) {
    auto reached = s.getBool(step.guard);
    if (!reached || !reached.value())
      continue;
    os << "\nState " << ++n << " " << step.location << " function " << step.function << "\n"
       << "  " << step.name << " = " << valueOf(s, step) << "\n";
  }
}

} // namespace vereda::witness
