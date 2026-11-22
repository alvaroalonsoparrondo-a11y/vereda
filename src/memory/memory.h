// Stage memory: (object, offset) pointers and byte-addressed memory (plan,
// section 4.4). A pointer is one bitvector: a 32-bit object id above a
// pointer-width offset. Memory is one byte array indexed by that pointer,
// plus a provenance array giving, per byte, the object of a stored pointer.
// Object 0 is null. Each object has a symbolic base address, above the
// previous object's end with a gap of at least one byte; addresses matter
// only for ptrtoint, inttoptr and ordered pointer comparison. Layout
// constraints hold only on paths where the object exists.
//
// A byte written at a constant pointer stays in the state's map of known
// bytes and reaches the arrays only when an access at a pointer that may
// alias it needs them (plan, section 4.2: a load from a known store). Most
// scalar globals and locals at a fixed address then never touch the arrays.
// At a join, an object whose two sides hold different values that multiply,
// divide or take a remainder goes to the arrays, so that the solver works on
// that arithmetic only where a read needs it.
#pragma once
#include "encode/terms.h"
#include <camada/camada.h>
#include <llvm/ADT/DenseMap.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/DataLayout.h>
#include <llvm/IR/Module.h>
#include <optional>
#include <functional>
#include <map>
#include <memory>
#include <vector>

namespace vereda::memory {

struct State {
  camada::SMTExprRef data; // pointer -> byte
  camada::SMTExprRef prov; // pointer -> object id of a stored pointer's byte
  struct Cell {
    camada::SMTExprRef data, prov;
  };
  // Bytes at constant (object, offset), newer than data and prov. Shared
  // between copies of the state and copied on the first write.
  using Known = std::map<std::pair<uint64_t, uint64_t>, Cell>;
  std::shared_ptr<Known> known;
};

class Memory {
public:
  Memory(encode::Terms &t, const llvm::DataLayout &dl);

  unsigned pointerBits() const { return ptrBits; }
  const llvm::DataLayout &layout() const { return dl; }
  camada::SMTSortRef pointerSort();
  camada::SMTExprRef null();
  camada::SMTExprRef object(camada::SMTExprRef p);
  camada::SMTExprRef offset(camada::SMTExprRef p);
  // p moved by delta bytes, a pointer-width bitvector.
  camada::SMTExprRef advance(camada::SMTExprRef p, camada::SMTExprRef delta);

  // Whether an allocator accepts an object of size bytes: at most
  // PTRDIFF_MAX, as glibc's malloc. It depends on the size alone, so the
  // solver cannot make a small allocation fail by placing earlier objects.
  camada::SMTExprRef fits(camada::SMTExprRef size);
  // A new object of size bytes (pointer-width term) that exists when exists
  // holds; its layout constraints bind only then. Returns its start.
  camada::SMTExprRef allocate(camada::SMTExprRef size, uint64_t align,
                              camada::SMTExprRef exists);
  // Allocates every global of m; their initialisers go in with initialise().
  void allocateGlobals(const llvm::Module &m);
  camada::SMTExprRef global(const llvm::GlobalValue *g) const;
  // Writes every global's initialiser into st; valueOf encodes constants
  // that are pointers into other globals.
  void initialise(State &st, const llvm::Module &m,
                  const std::function<camada::SMTExprRef(const llvm::Constant *)> &valueOf);

  camada::SMTExprRef address(camada::SMTExprRef p);   // ptrtoint
  camada::SMTExprRef fromAddress(camada::SMTExprRef a); // inttoptr

  // The guard of the code being walked: an access at ite(c, p, q) whose c
  // or not c it implies goes to one side only.
  void setContext(camada::SMTExprRef guard) { context = std::move(guard); }

  State initial(); // nondet contents
  State ite(camada::SMTExprRef c, const State &a, const State &b);
  // Loads and stores of integers (i1 as a byte) and pointers.
  camada::SMTExprRef load(State &st, camada::SMTExprRef p, llvm::Type *ty);
  void store(State &st, camada::SMTExprRef p, camada::SMTExprRef v, llvm::Type *ty);
  void set(State &st, camada::SMTExprRef p, camada::SMTExprRef byte, uint64_t n);
  void copy(State &st, camada::SMTExprRef dst, camada::SMTExprRef src, uint64_t n);

private:
  camada::SMTExprRef ptr(camada::SMTExprRef obj, camada::SMTExprRef off);
  camada::SMTExprRef bytePtr(camada::SMTExprRef p, uint64_t i);
  camada::SMTExprRef base(camada::SMTExprRef obj);
  bool hasPadding(llvm::Type *ty) const;
  using Key = std::pair<uint64_t, uint64_t>;
  std::optional<Key> key(camada::SMTExprRef p) const;
  camada::SMTExprRef ptr(const Key &k);
  // st's known bytes, made unshared so they can change.
  State::Known &own(State &st);
  // Moves the known bytes an access at p may alias into the arrays: those
  // of p's object, or all when the object is not constant.
  void prepare(State &st, camada::SMTExprRef p);
  // Moves the known bytes of object, or all known bytes, into the arrays.
  void flush(State &st, std::optional<uint64_t> object = std::nullopt);
  State::Cell readByte(const State &st, camada::SMTExprRef at);
  void writeByte(State &st, camada::SMTExprRef at, const State::Cell &c);
  void storeBytes(State &st, camada::SMTExprRef p, camada::SMTExprRef bits,
                  camada::SMTExprRef prov);
  void storeConstant(State &st, camada::SMTExprRef p, const llvm::Constant *c,
                     const std::function<camada::SMTExprRef(const llvm::Constant *)> &valueOf);

  struct Object {
    camada::SMTExprRef base, size;
  };

  encode::Terms &t;
  camada::SMTSolver &s;
  const llvm::DataLayout &dl;
  unsigned ptrBits;
  std::vector<Object> objects; // index = object id; 0 is null
  camada::SMTExprRef bases;    // object id -> base address, as an uninterpreted array
  camada::SMTExprRef end;      // first address after the last object
  llvm::DenseMap<const llvm::GlobalValue *, camada::SMTExprRef> globals;
  unsigned fresh = 0;
  camada::SMTExprRef context;
  // Which side of a split pointer the context picks: 1, 0, or -1 for both.
  int side(const camada::SMTExprRef &c);
};

} // namespace vereda::memory
