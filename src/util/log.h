// Stage util: progress and warning lines, and a stopwatch for stage timings.
#pragma once
#include <llvm/ADT/Twine.h>
#include <llvm/Support/Format.h>
#include <llvm/Support/raw_ostream.h>
#include <chrono>

namespace vereda::util {

inline void progress(const llvm::Twine &msg) { llvm::outs() << "[PROGRESS] " << msg << "\n"; }
inline void warning(const llvm::Twine &msg) { llvm::outs() << "[WARNING] " << msg << "\n"; }

class Stopwatch {
public:
  Stopwatch() : start(std::chrono::steady_clock::now()) {}
  // Seconds since construction, formatted like "0.012s".
  llvm::format_object<double> elapsed() const {
    std::chrono::duration<double> d = std::chrono::steady_clock::now() - start;
    return llvm::format("%.3fs", d.count());
  }

private:
  std::chrono::steady_clock::time_point start;
};

} // namespace vereda::util
