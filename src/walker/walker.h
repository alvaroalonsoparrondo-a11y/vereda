// Stage walker: symbolic execution over the rolled IR. Loops are unrolled on
// the fly and calls are walked in their own frame; nothing is copied.
#pragma once
#include "checks/checks.h"
#include "encode/encoder.h"
#include "memory/memory.h"
#include "walker/trace.h"
#include <llvm/IR/Function.h>
#include <llvm/Support/Error.h>

namespace vereda::walker {

struct Options {
  unsigned unwind = 0;             // loop iterations and recursion depth; 0 = until unreachable
  bool unwindingAssertions = true; // check the bound instead of assuming it
  bool forceMallocSuccess = false; // malloc never returns null
};

// Walks entry and everything it calls, binding values in the encoder and
// appending checks and trace steps. Returns an error for IR it cannot
// handle yet.
llvm::Error walk(llvm::Function &entry, const Options &opts, encode::Encoder &enc,
                 memory::Memory &mem, checks::Checks &checks, Trace &trace);

} // namespace vereda::walker
