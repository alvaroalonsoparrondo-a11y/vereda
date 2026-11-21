// Stage ir: debug-info helpers. Source locations come from clang's -g output.
#pragma once
#include <llvm/BinaryFormat/Dwarf.h>
#include <llvm/IR/DebugInfoMetadata.h>
#include <llvm/IR/DebugLoc.h>
#include <llvm/IR/DebugProgramInstruction.h>
#include <llvm/IR/Instruction.h>
#include <optional>
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

inline std::string location(const llvm::DebugLoc &loc) {
  if (!loc)
    return "<unknown>";
  return (loc->getFilename() + ":" + std::to_string(loc.getLine()) + ":" +
          std::to_string(loc.getCol()))
      .str();
}

// A #dbg_value record that assigns one whole value to a source variable.
struct DbgAssign {
  std::string name;
  const llvm::Value *value;
  bool isUnsigned;
  std::string location;
};

inline std::optional<DbgAssign> dbgAssign(const llvm::DbgRecord &rec) {
  auto *dvr = llvm::dyn_cast<llvm::DbgVariableRecord>(&rec);
  if (!dvr || !dvr->isDbgValue() || dvr->hasArgList() || dvr->getNumVariableLocationOps() != 1 ||
      dvr->getExpression()->getNumElements() != 0)
    return std::nullopt;
  const llvm::Value *v = dvr->getVariableLocationOp(0);
  if (!v)
    return std::nullopt;
  bool isUnsigned = false;
  if (auto *basic = llvm::dyn_cast_or_null<llvm::DIBasicType>(dvr->getVariable()->getType()))
    isUnsigned = basic->getEncoding() == llvm::dwarf::DW_ATE_unsigned ||
                 basic->getEncoding() == llvm::dwarf::DW_ATE_unsigned_char ||
                 basic->getEncoding() == llvm::dwarf::DW_ATE_boolean;
  // mem2reg leaves many records at line 0; the declaration is the next best place.
  const llvm::DILocalVariable *var = dvr->getVariable();
  std::string loc = dvr->getDebugLoc() && dvr->getDebugLoc().getLine() != 0
                        ? location(dvr->getDebugLoc())
                        : (var->getFilename() + ":" + std::to_string(var->getLine())).str();
  return DbgAssign{var->getName().str(), v, isUnsigned, loc};
}

} // namespace vereda::ir
