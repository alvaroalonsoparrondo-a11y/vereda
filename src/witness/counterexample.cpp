#include "witness/counterexample.h"

#include <llvm/Support/WithColor.h>

using namespace llvm;

namespace vereda::witness {

static const char *separator = "----------------------------------------------------";

// "99 (00000000 00000000 00000000 01100011)", or "?" when the model has no value.
static std::string valueOf(camada::SMTSolver &s, const walker::Step &step) {
  if (step.value->isBoolSort()) {
    auto b = s.getBool(step.value);
    return b ? (b.value() ? "true" : "false") : "?";
  }
  auto bits = s.getBVInBin(step.value);
  if (!bits)
    return "?";
  std::string out;
  if (step.value->getWidth() > 64)
    out = "0b" + bits.value();
  else if (step.isUnsigned)
    out = std::to_string(s.getBVUnsigned(step.value).value());
  else
    out = std::to_string(s.getBV(step.value).value());
  out += " (";
  for (size_t i = 0; i < bits.value().size(); ++i) {
    if (i && (bits.value().size() - i) % 8 == 0)
      out += ' ';
    out += bits.value()[i];
  }
  return out + ")";
}

void printCounterexample(camada::SMTSolver &s, const walker::Trace &trace,
                         const checks::Check &violated, raw_ostream &os) {
  os << "\n";
  WithColor(os, raw_ostream::RED, /*Bold=*/true) << "[Counterexample]";
  os << "\n\n";
  unsigned n = 0;
  for (const walker::Step &step : trace) {
    auto reached = s.getBool(step.guard);
    if (!reached || !reached.value())
      continue;
    os << "\nState " << ++n << " " << step.loc.str() << " thread 0\n" << separator << "\n  "
       << step.name << " = " << valueOf(s, step) << "\n";
  }
  os << "\nState " << ++n << " " << violated.loc.str() << " thread 0\n" << separator << "\n"
     << "Violated property:\n  " << violated.loc.str() << "\n  " << violated.comment << "\n\n";
}

} // namespace vereda::witness
