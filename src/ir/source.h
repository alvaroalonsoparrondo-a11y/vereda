// Stage ir: source text, for showing expressions in traces and properties.
#pragma once
#include <llvm/IR/Instruction.h>
#include <string>

namespace vereda::ir {

// The text between the parentheses of the call at inst's debug location,
// with whitespace collapsed, e.g. "x > 0 && x < 100" for
// __VERIFIER_assume(x > 0 && x < 100). Empty when the file cannot be read
// or the text does not look like a call.
std::string callArgumentText(const llvm::Instruction &inst);

} // namespace vereda::ir
