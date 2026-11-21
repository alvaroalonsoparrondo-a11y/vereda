#include "ir/load.h"

#include <llvm/IR/AttributeMask.h>
#include <llvm/IR/Attributes.h>
#include <llvm/IR/InstIterator.h>
#include <llvm/IR/InstrTypes.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Operator.h>
#include <llvm/IRReader/IRReader.h>
#include <llvm/Passes/PassBuilder.h>
#include <llvm/Support/SourceMgr.h>

using namespace llvm;

namespace vereda::ir {

// Poison-generating flags, attributes and metadata let LLVM assume no
// undefined behaviour; the walker must not. Strip them before InstCombine
// (which would fold checks with them) and after (which may infer them back).
static void stripUBAssumptions(Module &m) {
  AttributeMask ubAttrs;
  for (auto k : {Attribute::NoUndef, Attribute::NonNull, Attribute::Dereferenceable,
                 Attribute::DereferenceableOrNull, Attribute::Range, Attribute::OptimizeNone})
    ubAttrs.addAttribute(k);
  for (Function &f : m) {
    f.removeFnAttrs(ubAttrs);
    f.removeRetAttrs(ubAttrs);
    for (unsigned i = 0; i < f.arg_size(); ++i)
      f.removeParamAttrs(i, ubAttrs);
    for (Instruction &inst : instructions(f)) {
      if (isa<OverflowingBinaryOperator>(inst) || isa<TruncInst>(inst)) {
        inst.setHasNoUnsignedWrap(false);
        inst.setHasNoSignedWrap(false);
      }
      if (isa<PossiblyExactOperator>(inst))
        inst.setIsExact(false);
      if (isa<PossiblyNonNegInst>(inst))
        inst.setNonNeg(false);
      if (auto *d = dyn_cast<PossiblyDisjointInst>(&inst))
        d->setIsDisjoint(false);
      if (auto *c = dyn_cast<ICmpInst>(&inst))
        c->setSameSign(false);
      if (auto *gep = dyn_cast<GetElementPtrInst>(&inst))
        gep->setNoWrapFlags(GEPNoWrapFlags::none());
      if (auto *call = dyn_cast<CallBase>(&inst)) {
        call->removeFnAttrs(ubAttrs);
        call->removeRetAttrs(ubAttrs);
        for (unsigned i = 0; i < call->arg_size(); ++i)
          call->removeParamAttrs(i, ubAttrs);
      }
      for (unsigned md : {LLVMContext::MD_range, LLVMContext::MD_nonnull,
                          LLVMContext::MD_noundef, LLVMContext::MD_dereferenceable,
                          LLVMContext::MD_dereferenceable_or_null, LLVMContext::MD_align})
        inst.setMetadata(md, nullptr);
    }
  }
}

// -fno-finite-loops should have kept these out; any left would let LoopInfo
// and SCEV assume termination.
static bool hasMustProgress(const Module &m) {
  for (const Function &f : m) {
    if (f.hasFnAttribute(Attribute::MustProgress))
      return true;
    for (const Instruction &inst : instructions(f))
      if (MDNode *loopMD = inst.getMetadata(LLVMContext::MD_loop))
        for (const MDOperand &op : loopMD->operands())
          if (auto *node = dyn_cast<MDNode>(op))
            if (node->getNumOperands() > 0)
              if (auto *str = dyn_cast<MDString>(node->getOperand(0)))
                if (str->getString() == "llvm.loop.mustprogress")
                  return true;
  }
  return false;
}

static Error runPipeline(Module &m, StringRef pipeline) {
  LoopAnalysisManager lam;
  FunctionAnalysisManager fam;
  CGSCCAnalysisManager cgam;
  ModuleAnalysisManager mam;
  PassBuilder pb;
  pb.registerModuleAnalyses(mam);
  pb.registerCGSCCAnalyses(cgam);
  pb.registerFunctionAnalyses(fam);
  pb.registerLoopAnalyses(lam);
  pb.crossRegisterProxies(lam, fam, cgam, mam);
  ModulePassManager mpm;
  if (Error e = pb.parsePassPipeline(mpm, pipeline))
    return e;
  mpm.run(m, mam);
  return Error::success();
}

Expected<std::unique_ptr<Module>> load(StringRef path, LLVMContext &ctx) {
  SMDiagnostic diag;
  std::unique_ptr<Module> module = parseIRFile(path, diag, ctx);
  if (!module) {
    std::string msg;
    raw_string_ostream os(msg);
    diag.print(nullptr, os, /*ShowColors=*/false);
    return createStringError(inconvertibleErrorCode(), StringRef(msg).rtrim());
  }
  if (hasMustProgress(*module))
    return createStringError(inconvertibleErrorCode(),
                             path + " carries mustprogress; compile with -fno-finite-loops");

  stripUBAssumptions(*module);
  if (Error e = runPipeline(*module, "function(mem2reg,sroa)"))
    return std::move(e);
  // ponytail: plain instcombine; the plan wants a "careful" one that folds
  // nothing on undefined behaviour. Revisit when a folded check shows up.
  if (Error e = runPipeline(*module, "function(instcombine,loop-simplify,lcssa)"))
    return std::move(e);
  stripUBAssumptions(*module);
  return module;
}

} // namespace vereda::ir
