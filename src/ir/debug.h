// Stage ir: debug-info helpers. Source locations come from clang's -g output.
#pragma once
#include <llvm/BinaryFormat/Dwarf.h>
#include <llvm/IR/DebugInfoMetadata.h>
#include <llvm/IR/DebugLoc.h>
#include <llvm/IR/DebugProgramInstruction.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Instruction.h>
#include <optional>
#include <string>

namespace vereda::ir {

// A source location in ESBMC's spelling: "file F line L column C function Fn".
struct SourceLoc {
  std::string file;
  unsigned line = 0;
  unsigned col = 0;
  std::string function;

  std::string str() const {
    std::string out = "file " + file + " line " + std::to_string(line);
    if (col)
      out += " column " + std::to_string(col);
    return out + " function " + function;
  }
};

inline SourceLoc location(const llvm::DebugLoc &loc, llvm::StringRef function) {
  if (!loc)
    return {"<unknown>", 0, 0, function.str()};
  return {loc->getFilename().str(), loc.getLine(), loc.getCol(), function.str()};
}

inline SourceLoc location(const llvm::Instruction &inst) {
  return location(inst.getDebugLoc(), inst.getFunction()->getName());
}

// A #dbg_value record that assigns one whole value to a source variable.
struct DbgAssign {
  std::string name;
  const llvm::Value *value;
  bool isUnsigned;
  SourceLoc loc;
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
  llvm::StringRef function = dvr->getFunction()->getName();
  SourceLoc loc = dvr->getDebugLoc() && dvr->getDebugLoc().getLine() != 0
                      ? location(dvr->getDebugLoc(), function)
                      : SourceLoc{var->getFilename().str(), var->getLine(), 0, function.str()};
  return DbgAssign{var->getName().str(), v, isUnsigned, loc};
}

} // namespace vereda::ir
