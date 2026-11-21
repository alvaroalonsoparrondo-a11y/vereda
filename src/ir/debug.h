// Stage ir: debug-info helpers. Source locations come from clang's -g output.
#pragma once
#include <llvm/IR/DebugInfoMetadata.h>
#include <llvm/IR/DebugLoc.h>
#include <llvm/IR/Instruction.h>
#include <string>

namespace vereda::ir {

// "file:line:col", or "<unknown>" when the instruction carries no location.
inline std::string location(const llvm::Instruction &inst) {
  const llvm::DebugLoc &loc = inst.getDebugLoc();
  if (!loc)
    return "<unknown>";
  return (loc->getFilename() + ":" + std::to_string(loc.getLine()) + ":" +
          std::to_string(loc.getCol()))
      .str();
}

} // namespace vereda::ir
