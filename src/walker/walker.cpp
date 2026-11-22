#include "walker/walker.h"

#include "ir/debug.h"
#include "ir/sanitizer.h"
#include "ir/source.h"
#include "util/log.h"
#include <llvm/ADT/DenseMap.h>
#include <llvm/ADT/MapVector.h>
#include <llvm/ADT/PostOrderIterator.h>
#include <llvm/ADT/SmallPtrSet.h>
#include <llvm/Analysis/LoopInfo.h>
#include <llvm/IR/CFG.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/Dominators.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/InstIterator.h>
#include <algorithm>
#include <memory>

using namespace llvm;
using camada::SMTExprRef;
using vereda::encode::Unsupported;

namespace vereda::walker {

namespace {

// Per-function CFG facts, computed once.
struct FunctionInfo {
  explicit FunctionInfo(Function &f) : dt(f), li(dt) {
    for (BasicBlock *bb : ReversePostOrderTraversal<Function *>(&f))
      rpo.push_back(bb);
    DenseMap<const BasicBlock *, unsigned> index;
    for (unsigned i = 0; i < rpo.size(); ++i)
      index[rpo[i]] = i;
    // A retreating edge must be a loop back edge, or the CFG is irreducible.
    for (BasicBlock *bb : rpo)
      for (BasicBlock *succ : successors(bb))
        if (index.lookup(succ) <= index.lookup(bb) && !dt.dominates(succ, bb))
          throw Unsupported("irreducible control flow in " + f.getName().str());
    for (BasicBlock *bb : rpo)
      if (li.isLoopHeader(bb))
        loopNumber[li.getLoopFor(bb)] = loopNumber.size();
  }

  DominatorTree dt;
  LoopInfo li;
  std::vector<BasicBlock *> rpo;
  DenseMap<const Loop *, unsigned> loopNumber; // ESBMC's "loop N", per function
};

// One way into a block: the edge's guard and the values its phis take on it,
// captured when the edge is taken, since a later iteration rebinds them.
struct Arrival {
  SMTExprRef guard;
  SmallVector<SMTExprRef, 2> phiValues;
};

struct Frame {
  DenseMap<const BasicBlock *, SmallVector<Arrival, 2>> arrivals;
  SmallVector<std::pair<SMTExprRef, SMTExprRef>, 2> returns; // guard, value
};

class Walk {
public:
  Walk(const Options &opts, encode::Encoder &enc, checks::Checks &checks, Trace &trace)
      : opts(opts), enc(enc), s(enc.solver()), checks(checks), trace(trace) {}

  void entry(Function &f) {
    for (Argument &arg : f.args())
      enc.bind(&arg, enc.fresh(arg.getType(), "arg_" + arg.getName().str()));
    function(f, s.mkBool(true));
  }

private:
  FunctionInfo &info(Function &f) {
    std::unique_ptr<FunctionInfo> &fi = infos[&f];
    if (!fi)
      fi = std::make_unique<FunctionInfo>(f);
    return *fi;
  }

  // Walks f's body from a call guarded by guard. Returns the frame's return
  // arrivals.
  Frame function(Function &f, SMTExprRef guard) {
    Frame frame;
    frame.arrivals[&f.getEntryBlock()].push_back({guard, {}});
    stack.push_back(&f);
    region(frame, info(f), nullptr);
    stack.pop_back();
    return frame;
  }

  // Walks the blocks of loop l, or of the whole function when l is null, in
  // reverse post-order with each inner loop collapsed to its header.
  void region(Frame &frame, FunctionInfo &fi, Loop *l) {
    for (BasicBlock *bb : fi.rpo) {
      if (l && !l->contains(bb))
        continue;
      Loop *inner = fi.li.getLoopFor(bb);
      if (inner == l) {
        block(frame, *bb);
        continue;
      }
      while (inner->getParentLoop() != l)
        inner = inner->getParentLoop();
      if (inner->getHeader() == bb)
        loop(frame, fi, inner);
    }
  }

  void loop(Frame &frame, FunctionInfo &fi, Loop *l) {
    BasicBlock *header = l->getHeader();
    unsigned number = fi.loopNumber.lookup(l);
    for (unsigned i = 0;; ++i) {
      auto it = frame.arrivals.find(header);
      if (it == frame.arrivals.end() || it->second.empty())
        return;
      if (i > 0) {
        SMTExprRef reached = anyGuard(it->second);
        if (opts.unwind && i >= opts.unwind) {
          unwound(Unwound::Loop, number, loopLocation(l), reached, l);
          it->second.clear();
          return;
        }
        // ponytail: one solver call per iteration without --unwind; term
        // folding will settle most of these without the solver.
        if (!opts.unwind && s.checkSatAssuming({reached}) == camada::CheckResult::UNSAT) {
          it->second.clear();
          return;
        }
        outs() << "Unwinding loop " << number << " iteration " << i << "   "
               << loopLocation(l).str() << "\n";
      }
      region(frame, fi, l);
    }
  }

  enum class Unwound { Loop, Recursion };

  // The bound was hit with guard reachable: an unwinding assertion, or an
  // assumption that cuts the path. key is the loop or the recursive call.
  void unwound(Unwound kind, unsigned number, const ir::SourceLoc &loc, SMTExprRef reached,
               const void *key) {
    if (!opts.unwindingAssertions)
      return;
    bool isLoop = kind == Unwound::Loop;
    std::string comment = isLoop ? "unwinding assertion loop " + std::to_string(number)
                                 : "recursion unwinding assertion";
    claim(isLoop ? checks::Property::Unwinding : checks::Property::Recursion, loc, comment, "",
          number, reached, key);
  }

  static ir::SourceLoc loopLocation(Loop *l) {
    DebugLoc loc = l->getStartLoc();
    return ir::location(loc, l->getHeader()->getParent()->getName());
  }

  SMTExprRef anyGuard(const SmallVectorImpl<Arrival> &arrivals) {
    SMTExprRef g = arrivals[0].guard;
    for (unsigned i = 1; i < arrivals.size(); ++i)
      g = s.mkOr(g, arrivals[i].guard);
    return g;
  }

  void block(Frame &frame, BasicBlock &bb) {
    SmallVector<Arrival, 2> arrivals = std::move(frame.arrivals[&bb]);
    frame.arrivals.erase(&bb);
    if (arrivals.empty()) // no edge into bb was taken in this pass
      return;
    SMTExprRef guard = anyGuard(arrivals);

    unsigned p = 0;
    for (PHINode &phi : bb.phis()) {
      SMTExprRef r = arrivals[0].phiValues[p];
      for (unsigned i = 1; i < arrivals.size(); ++i)
        r = s.mkIte(arrivals[i].guard, arrivals[i].phiValues[p], r);
      enc.bind(&phi, r);
      ++p;
    }

    for (Instruction &inst : bb) {
      for (const DbgRecord &rec : inst.getDbgRecordRange())
        if (std::optional<ir::DbgAssign> a = ir::dbgAssign(rec))
          if (SMTExprRef v = traceValue(a->value))
            trace.push_back({Step::Assignment, guard, a->loc, a->name, v, a->isUnsigned});
      if (isa<PHINode>(inst))
        continue;
      if (inst.isTerminator())
        terminator(frame, inst, guard);
      else if (auto *c = dyn_cast<CallBase>(&inst))
        guard = call(*c, guard);
      else
        enc.encode(inst);
    }
  }

  // A debug record's value for the trace, or null when it has none yet.
  // LCSSA does not route debug uses, so a record can name a value from a
  // block not walked in this pass; the trace skips it.
  SMTExprRef traceValue(const Value *v) {
    if (!v->getType()->isIntegerTy())
      return {};
    if (isa<Instruction>(v) || isa<Argument>(v))
      return enc.bound(v);
    return isa<Constant>(v) ? enc.value(v) : SMTExprRef();
  }

  void arrive(Frame &frame, BasicBlock *pred, BasicBlock *succ, SMTExprRef guard) {
    Arrival a{guard, {}};
    for (PHINode &phi : succ->phis())
      a.phiValues.push_back(enc.value(phi.getIncomingValueForBlock(pred)));
    frame.arrivals[succ].push_back(std::move(a));
  }

  void terminator(Frame &frame, Instruction &term, SMTExprRef guard) {
    BasicBlock *bb = term.getParent();
    if (auto *br = dyn_cast<BranchInst>(&term)) {
      if (br->isUnconditional() || br->getSuccessor(0) == br->getSuccessor(1)) {
        arrive(frame, bb, br->getSuccessor(0), guard);
        return;
      }
      SMTExprRef c = enc.value(br->getCondition());
      arrive(frame, bb, br->getSuccessor(0), s.mkAnd(guard, c));
      arrive(frame, bb, br->getSuccessor(1), s.mkAnd(guard, s.mkNot(c)));
    } else if (auto *sw = dyn_cast<SwitchInst>(&term)) {
      SMTExprRef cond = enc.value(sw->getCondition());
      SMTExprRef anyCase = s.mkBool(false);
      MapVector<BasicBlock *, SMTExprRef> taken; // in case order, for a stable formula
      for (const auto &c : sw->cases()) {
        SMTExprRef eq = s.mkEqual(cond, enc.value(c.getCaseValue()));
        anyCase = s.mkOr(anyCase, eq);
        SMTExprRef &t = taken[c.getCaseSuccessor()];
        t = t ? s.mkOr(t, eq) : eq;
      }
      SMTExprRef &d = taken[sw->getDefaultDest()];
      d = d ? s.mkOr(d, s.mkNot(anyCase)) : s.mkNot(anyCase);
      for (auto &[succ, t] : taken)
        arrive(frame, bb, succ, s.mkAnd(guard, t));
    } else if (auto *ret = dyn_cast<ReturnInst>(&term)) {
      Value *v = ret->getReturnValue();
      frame.returns.push_back({guard, v ? enc.value(v) : SMTExprRef()});
    } else if (isa<UnreachableInst>(term)) {
      // Clang ends a block with unreachable after a call that never returns:
      // the path ends there. Anywhere else it is __builtin_unreachable,
      // which ESBMC checks by default.
      auto *prev = dyn_cast_or_null<CallBase>(term.getPrevNode());
      if (!prev || !prev->doesNotReturn())
        assertion(term, guard, "__builtin_unreachable", "");
    } else {
      throw Unsupported(std::string("terminator ") + term.getOpcodeName());
    }
  }

  // Returns the path condition after the call: unchanged, strengthened by an
  // assume, or false when the callee does not return.
  SMTExprRef call(CallBase &c, SMTExprRef guard) {
    // getCalledFunction() is null for an indirect call, and also for a direct
    // one whose type disagrees with the definition (K&R, or across files).
    Function *callee = c.getCalledFunction();
    if (!callee) {
      if (auto *f = dyn_cast<Function>(c.getCalledOperand()->stripPointerCasts()))
        throw Unsupported("call to " + f->getName().str() + " with a mismatched signature at " +
                          ir::location(c).str());
      throw Unsupported("indirect call at " + ir::location(c).str());
    }
    StringRef name = callee->getName();
    std::string tag = name.str() + "@" + ir::location(c).str();

    if (callee->isIntrinsic()) {
      if (enc.intrinsic(c))
        return guard;
      if (name.starts_with("llvm.lifetime") || name.starts_with("llvm.dbg") ||
          name == "llvm.assume")
        return guard;
      if (name == "llvm.trap") // __builtin_trap: an abnormal end, not an error, as in ESBMC
        return s.mkBool(false);
      if (name == "llvm.ubsantrap") { // a clang sanitizer check failed
        auto *code = cast<ConstantInt>(c.getArgOperand(0));
        assertion(c, guard, ir::sanitizerCheck(code->getZExtValue()), "");
        return s.mkBool(false);
      }
      throw Unsupported("intrinsic " + name.str());
    }
    if (!callee->isDeclaration())
      return enter(c, *callee, guard);

    // Bodyless verifier functions, as ESBMC treats them by default: a defined
    // one is an ordinary call. An unreachability-intrinsic flag that skips
    // the body comes with the SV-COMP wrapper.
    if (name.starts_with("__VERIFIER_nondet_")) {
      enc.bind(&c, enc.fresh(c.getType(), tag));
      return guard;
    }
    if (name == "__VERIFIER_assume") {
      trace.push_back({Step::Assumption, guard, ir::location(c), ir::callArgumentText(c), {}});
      return s.mkAnd(guard, enc.isTrue(c.getArgOperand(0)));
    }
    if (name == "__assert_fail" || name == "reach_error" || name == "__VERIFIER_error") {
      assertion(c, guard, name.str(), "");
      return s.mkBool(false);
    }
    if (name == "__VERIFIER_assert") {
      assertion(c, s.mkAnd(guard, s.mkNot(enc.isTrue(c.getArgOperand(0)))), name.str(),
                ir::callArgumentText(c));
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

  // Walks a defined callee in a new frame.
  SMTExprRef enter(CallBase &c, Function &callee, SMTExprRef guard) {
    if (callee.isVarArg())
      throw Unsupported("variadic function " + callee.getName().str());
    unsigned depth = std::count(stack.begin(), stack.end(), &callee);
    if (depth > 0) {
      bool cut = false;
      if (opts.unwind && depth >= opts.unwind) {
        unsigned &number = recursionNumber[&c];
        if (!number)
          number = ++recursionsIn[c.getFunction()];
        unwound(Unwound::Recursion, number, ir::location(c), guard, &c);
        cut = true;
      } else if (!opts.unwind && s.checkSatAssuming({guard}) == camada::CheckResult::UNSAT) {
        cut = true;
      }
      if (cut) { // no path continues; the result only has to be bound
        if (!c.getType()->isVoidTy())
          enc.bind(&c, enc.fresh(c.getType(), "unwound"));
        return s.mkBool(false);
      }
    }

    SmallVector<SMTExprRef, 4> actuals;
    for (Value *arg : c.args())
      actuals.push_back(enc.value(arg));
    // A recursive call rebinds the caller's own values; keep them.
    SmallVector<std::pair<const Value *, SMTExprRef>, 0> saved;
    if (depth > 0) {
      for (Argument &arg : callee.args())
        if (SMTExprRef t = enc.bound(&arg))
          saved.push_back({&arg, t});
      for (Instruction &inst : instructions(callee))
        if (SMTExprRef t = enc.bound(&inst))
          saved.push_back({&inst, t});
    }
    for (Argument &arg : callee.args())
      enc.bind(&arg, actuals[arg.getArgNo()]);

    Frame frame = function(callee, guard);

    SMTExprRef after = s.mkBool(false), result;
    for (auto &[g, v] : frame.returns) {
      after = frame.returns.size() == 1 ? g : s.mkOr(after, g);
      result = result ? s.mkIte(g, v, result) : v;
    }
    for (auto &[v, t] : saved)
      enc.bind(v, t);
    if (!c.getType()->isVoidTy())
      enc.bind(&c, result ? result : enc.fresh(c.getType(), "noreturn"));
    return after;
  }

  // A check at inst, violated when violated holds; comment names it.
  void assertion(const Instruction &inst, SMTExprRef violated, std::string comment,
                 std::string expr) {
    unsigned &index = assertionNumber[&inst];
    if (!index)
      index = ++assertionsIn[inst.getFunction()];
    claim(checks::Property::Assertion, ir::location(inst), std::move(comment), std::move(expr),
          index, violated, &inst);
  }

  // One claim per source construct, keyed by its instruction or loop:
  // reaching it again, in another iteration or context, ORs into the check.
  void claim(checks::Property property, const ir::SourceLoc &loc, std::string comment,
             std::string expr, unsigned index, SMTExprRef violated, const void *key) {
    auto [it, inserted] = claims.try_emplace(key, checks.size());
    trace.push_back({Step::Check, violated, loc, "", {}, false, it->second});
    if (!inserted) {
      checks[it->second].violated = s.mkOr(checks[it->second].violated, violated);
      return;
    }
    checks.push_back({property, loc, std::move(comment), std::move(expr), index, violated});
  }

  const Options &opts;
  encode::Encoder &enc;
  camada::SMTSolver &s;
  checks::Checks &checks;
  Trace &trace;
  DenseMap<const Function *, std::unique_ptr<FunctionInfo>> infos;
  SmallVector<const Function *, 8> stack;
  DenseMap<const void *, unsigned> claims; // source construct -> index in checks
  DenseMap<const Instruction *, unsigned> assertionNumber;
  DenseMap<const Function *, unsigned> assertionsIn;
  DenseMap<const CallBase *, unsigned> recursionNumber;
  DenseMap<const Function *, unsigned> recursionsIn;
  SmallPtrSet<const Function *, 8> warned;
};

} // namespace

Error walk(Function &entry, const Options &opts, encode::Encoder &enc, checks::Checks &checks,
           Trace &trace) {
  try {
    Walk(opts, enc, checks, trace).entry(entry);
  } catch (const Unsupported &e) {
    return createStringError(inconvertibleErrorCode(), "unsupported: %s", e.what());
  }
  return Error::success();
}

} // namespace vereda::walker
