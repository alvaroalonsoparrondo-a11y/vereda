#include "walker/walker.h"

#include "ir/debug.h"
#include "util/log.h"
#include <llvm/ADT/DenseMap.h>
#include <llvm/ADT/SmallPtrSet.h>
#include <llvm/ADT/PostOrderIterator.h>
#include <llvm/IR/CFG.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/Instructions.h>

using namespace llvm;
using camada::SMTExprRef;
using vereda::encode::Unsupported;

namespace vereda::walker {

namespace {

class Walk {
public:
  Walk(encode::Encoder &enc, checks::Checks &checks, Trace &trace)
      : enc(enc), s(enc.solver()), checks(checks), trace(trace) {}

  void function(Function &f) {
    for (Argument &arg : f.args())
      enc.bind(&arg, enc.fresh(arg.getType(), "arg_" + arg.getName().str()));
    for (BasicBlock *bb : ReversePostOrderTraversal<Function *>(&f))
      block(*bb, &f.getEntryBlock() == bb);
  }

private:
  // Path condition for taking the edge pred -> succ.
  SMTExprRef edge(const BasicBlock *pred, const BasicBlock *succ) {
    auto it = exitGuard.find(pred);
    if (it == exitGuard.end())
      throw Unsupported("loops");
    SMTExprRef g = it->second;
    const Instruction *term = pred->getTerminator();
    if (auto *br = dyn_cast<BranchInst>(term)) {
      if (br->isConditional() && br->getSuccessor(0) != br->getSuccessor(1)) {
        SMTExprRef c = enc.value(br->getCondition());
        g = s.mkAnd(g, br->getSuccessor(0) == succ ? c : s.mkNot(c));
      }
    } else if (auto *sw = dyn_cast<SwitchInst>(term)) {
      SMTExprRef cond = enc.value(sw->getCondition());
      SMTExprRef taken = s.mkBool(false), anyCase = s.mkBool(false);
      for (const auto &c : sw->cases()) {
        SMTExprRef eq = s.mkEqual(cond, enc.value(c.getCaseValue()));
        anyCase = s.mkOr(anyCase, eq);
        if (c.getCaseSuccessor() == succ)
          taken = s.mkOr(taken, eq);
      }
      if (sw->getDefaultDest() == succ)
        taken = s.mkOr(taken, s.mkNot(anyCase));
      g = s.mkAnd(g, taken);
    } else {
      throw Unsupported(std::string("terminator ") + term->getOpcodeName());
    }
    return g;
  }

  void block(BasicBlock &bb, bool isEntry) {
    SMTExprRef guard = s.mkBool(isEntry);
    for (const BasicBlock *pred : predecessors(&bb))
      guard = s.mkOr(guard, edge(pred, &bb));

    for (PHINode &phi : bb.phis()) {
      SMTExprRef r = enc.value(phi.getIncomingValue(0));
      for (unsigned i = 1; i < phi.getNumIncomingValues(); ++i)
        r = s.mkIte(edge(phi.getIncomingBlock(i), &bb), enc.value(phi.getIncomingValue(i)), r);
      enc.bind(&phi, r);
    }
    for (Instruction &inst : bb) {
      for (const DbgRecord &rec : inst.getDbgRecordRange())
        if (std::optional<ir::DbgAssign> a = ir::dbgAssign(rec))
          if (a->value->getType()->isIntegerTy())
            trace.push_back({guard, a->location, bb.getParent()->getName().str(), a->name,
                             enc.value(a->value), a->isUnsigned});
      if (isa<PHINode>(inst))
        continue;
      if (inst.isTerminator()) {
        if (!isa<BranchInst, SwitchInst, ReturnInst, UnreachableInst>(inst))
          throw Unsupported(std::string("terminator ") + inst.getOpcodeName());
        continue;
      }
      if (auto *c = dyn_cast<CallBase>(&inst))
        guard = call(*c, guard);
      else
        enc.encode(inst);
    }
    exitGuard[&bb] = guard;
  }

  // Returns the path condition after the call: unchanged, strengthened by an
  // assume, or false when the callee does not return.
  SMTExprRef call(CallBase &c, SMTExprRef guard) {
    Function *callee = c.getCalledFunction();
    if (!callee)
      throw Unsupported("indirect call at " + ir::location(c));
    StringRef name = callee->getName();
    std::string tag = name.str() + "@" + ir::location(c);

    if (callee->isIntrinsic()) {
      if (name.starts_with("llvm.lifetime") || name.starts_with("llvm.dbg") ||
          name == "llvm.assume")
        return guard;
      if (name == "llvm.trap" || name == "llvm.ubsantrap")
        return s.mkBool(false);
      throw Unsupported("intrinsic " + name.str());
    }
    if (!callee->isDeclaration())
      throw Unsupported("call to " + name.str()); // walked in a new context, later

    // Bodyless verifier functions, as ESBMC treats them by default: a defined
    // one is an ordinary call. An unreachability-intrinsic flag that skips
    // the body comes with the SV-COMP wrapper.
    if (name.starts_with("__VERIFIER_nondet_")) {
      enc.bind(&c, enc.fresh(c.getType(), tag));
      return guard;
    }
    if (name == "__VERIFIER_assume")
      return s.mkAnd(guard, enc.isTrue(c.getArgOperand(0)));
    if (name == "__assert_fail" || name == "reach_error" || name == "__VERIFIER_error" ||
        name == "__builtin_unreachable") {
      checks.push_back({checks::Property::Reachability, ir::location(c), "assertion fails",
                        guard});
      return s.mkBool(false);
    }
    if (name == "__VERIFIER_assert") {
      checks.push_back({checks::Property::Reachability, ir::location(c), "assertion fails",
                        s.mkAnd(guard, s.mkNot(enc.isTrue(c.getArgOperand(0))))});
      return guard;
    }
    if (name == "abort" || name == "exit" || name == "_Exit")
      return s.mkBool(false);
    // ponytail: an unknown external returns an unconstrained value. Sound
    // while nothing has memory; revisit with the memory model.
    if (warned.insert(callee).second)
      util::warning("no body for function " + name);
    if (!c.getType()->isVoidTy())
      enc.bind(&c, enc.fresh(c.getType(), tag));
    return guard;
  }

  encode::Encoder &enc;
  camada::SMTSolver &s;
  checks::Checks &checks;
  Trace &trace;
  DenseMap<const BasicBlock *, SMTExprRef> exitGuard; // path condition at block end
  SmallPtrSet<const Function *, 8> warned;
};

} // namespace

Error walk(Function &entry, encode::Encoder &enc, checks::Checks &checks, Trace &trace) {
  try {
    Walk(enc, checks, trace).function(entry);
  } catch (const Unsupported &e) {
    return createStringError(inconvertibleErrorCode(), "unsupported: %s", e.what());
  }
  return Error::success();
}

} // namespace vereda::walker
