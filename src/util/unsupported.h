// Stage util: IR a stage cannot handle yet. The driver turns it into UNKNOWN.
#pragma once
#include <stdexcept>

namespace vereda {

struct Unsupported : std::runtime_error {
  using std::runtime_error::runtime_error;
};

} // namespace vereda
