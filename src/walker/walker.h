// Stage walker: symbolic execution over the rolled IR. For now one function,
// no loops, no memory, calls only to the verifier intrinsics.
#pragma once
#include "checks/checks.h"
#include "encode/encoder.h"
#include "walker/trace.h"
#include <llvm/IR/Function.h>
#include <llvm/Support/Error.h>

namespace vereda::walker {

// Walks entry once in reverse post-order, binding every value in the encoder
// and appending checks and trace steps. Returns an error for IR it cannot
// handle yet.
llvm::Error walk(llvm::Function &entry, encode::Encoder &enc, checks::Checks &checks,
                 Trace &trace);

} // namespace vereda::walker
