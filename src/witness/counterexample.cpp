#include "witness/counterexample.h"

#include <llvm/Support/WithColor.h>

using namespace llvm;

namespace vereda::witness {

static const char *separator = "----------------------------------------------------";

// Prints "99 (00000000 00000000 00000000 01100011)", the bits in grey, or
// "?" when the model has no value.
static void printValue(camada::SMTSolver &s, const walker::Step &step, raw_ostream &os) {
  if (step.value->isBoolSort()) {
    auto b = s.getBool(step.value);
    os << (b ? (b.value() ? "true" : "false") : "?");
    return;
  }
  auto bits = s.getBVInBin(step.value);
  if (!bits) {
    os << "?";
    return;
  }
  if (step.value->getWidth() > 64)
    os << "0b" << bits.value();
  else if (step.isUnsigned)
    os << s.getBVUnsigned(step.value).value();
  else
    os << s.getBV(step.value).value();
  std::string grouped = " (";
  for (size_t i = 0; i < bits.value().size(); ++i) {
    if (i && (bits.value().size() - i) % 8 == 0)
      grouped += ' ';
    grouped += bits.value()[i];
  }
  WithColor(os, raw_ostream::BRIGHT_BLACK) << grouped << ")";
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
    if (step.kind == walker::Step::Assumption) {
      os << "\nAssumption:\n  " << step.loc.str() << "\n  " << step.text << "\n";
      continue;
    }
    os << "\nState " << ++n << " " << step.loc.str() << " thread 0\n" << separator << "\n  "
       << step.text << " = ";
    printValue(s, step, os);
    os << "\n";
  }
  os << "\nState " << ++n << " " << violated.loc.str() << " thread 0\n" << separator << "\n"
     << "Violated property:\n  " << violated.loc.str() << "\n  " << violated.comment << "\n";
  if (!violated.expr.empty())
    os << "  " << violated.expr << "\n";
  os << "\n";
}

} // namespace vereda::witness
