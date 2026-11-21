// Verifier binary. Takes LLVM bitcode or IR, runs the short pass list from the
// plan (section 4.1), and either dumps the IR or hands it to the walker (not
// written yet; for now a camada smoke query stands in).
#include <camada/camada.h>
#include <camada/camadafeatures.h>
#include <llvm/IR/AttributeMask.h>
#include <llvm/IR/Attributes.h>
#include <llvm/IR/InstIterator.h>
#include <llvm/IR/InstrTypes.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Operator.h>
#include <llvm/IRReader/IRReader.h>
#include <llvm/Passes/PassBuilder.h>
#include <llvm/Support/CommandLine.h>
#include <llvm/Support/SourceMgr.h>
#include <llvm/Support/raw_ostream.h>

using namespace llvm;

static cl::opt<std::string> inputFile(cl::Positional, cl::desc("<file.bc|file.ll>"),
                                      cl::Required);
static cl::opt<bool> dumpIR("dump-ir", cl::desc("Print the IR after the pass list and exit"));

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

static void runPipeline(Module &m, StringRef pipeline) {
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
    report_fatal_error(std::move(e));
  mpm.run(m, mam);
}

int main(int argc, char **argv) {
  cl::ParseCommandLineOptions(argc, argv, "vereda: LLVM-IR verifier\n");
  LLVMContext ctx;
  SMDiagnostic err;
  std::unique_ptr<Module> module = parseIRFile(inputFile, err, ctx);
  if (!module) {
    err.print(argv[0], errs());
    return 1;
  }
  if (hasMustProgress(*module)) {
    errs() << argv[0] << ": " << inputFile
           << " carries mustprogress; compile with -fno-finite-loops\n";
    return 1;
  }

  stripUBAssumptions(*module);
  runPipeline(*module, "function(mem2reg,sroa)");
  // ponytail: plain instcombine; the plan wants a "careful" one that folds
  // nothing on undefined behaviour. Revisit when a folded check shows up.
  runPipeline(*module, "function(instcombine,loop-simplify,lcssa)");
  stripUBAssumptions(*module);

  if (dumpIR) {
    module->print(outs(), nullptr);
    return 0;
  }

  for (const Function &f : *module)
    if (!f.isDeclaration())
      outs() << f.getName() << "\n";

#if CAMADA_HAVE_BITWUZLA
  camada::SMTSolverRef solver = camada::createBitwuzlaSolver();
#elif CAMADA_HAVE_Z3
  camada::SMTSolverRef solver = camada::createZ3Solver();
#else
#error "camada was built without Bitwuzla or Z3"
#endif
  camada::SMTExprRef x = solver->mkSymbol("x", solver->mkBVSort(32));
  solver->addConstraint(solver->mkEqual(x, solver->mkBVFromDec(7, 32)));
  bool sat = solver->check() == camada::CheckResult::SAT;
  outs() << "solver: " << (sat ? "sat" : "unsat") << "\n";
  return sat ? 0 : 1;
}
