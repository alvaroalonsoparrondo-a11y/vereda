// Stage ir: loads bitcode or textual IR and prepares it for the walker.
#pragma once
#include <llvm/IR/Module.h>
#include <llvm/Support/Error.h>
#include <memory>

namespace vereda::ir {

// Rejects mustprogress, strips the flags, attributes and metadata that let
// LLVM assume no undefined behaviour, and runs the short pass list from the
// plan (section 4.1): mem2reg, SROA, InstCombine, loop-simplify, LCSSA.
// Indirect calls become tests of the pointer and direct calls, and direct
// calls to a function of another type convert their arguments.
llvm::Expected<std::unique_ptr<llvm::Module>> load(llvm::StringRef path,
                                                   llvm::LLVMContext &ctx);

} // namespace vereda::ir
