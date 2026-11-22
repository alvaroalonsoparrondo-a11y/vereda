// Stage memory: (object, offset) pointers and byte-addressed memory (plan,
// section 4.4). A pointer is one bitvector: a 32-bit object id above a
// pointer-width offset. Memory is one byte array indexed by that pointer,
// plus a provenance array giving, per byte, the object of a stored pointer.
// Object 0 is null. Each object has a symbolic base address, above the
// previous object's end with a gap of at least one byte; addresses matter
// only for ptrtoint, inttoptr and ordered pointer comparison. Layout
// constraints hold only on paths where the object exists.
#pragma once
#include <camada/camada.h>
#include <llvm/ADT/DenseMap.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/DataLayout.h>
#include <llvm/IR/Module.h>
#include <functional>
#include <vector>

namespace vereda::memory {

struct State {
  camada::SMTExprRef data; // pointer -> byte
  camada::SMTExprRef prov; // pointer -> object id of a stored pointer's byte
};

class Memory {
public:
  Memory(camada::SMTSolver &s, const llvm::DataLayout &dl);

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

  State initial(); // nondet contents
  State ite(camada::SMTExprRef c, const State &a, const State &b);
  // Loads and stores of integers (i1 as a byte) and pointers.
  camada::SMTExprRef load(const State &st, camada::SMTExprRef p, llvm::Type *ty);
  void store(State &st, camada::SMTExprRef p, camada::SMTExprRef v, llvm::Type *ty);
  void set(State &st, camada::SMTExprRef p, camada::SMTExprRef byte, uint64_t n);
  void copy(State &st, camada::SMTExprRef dst, camada::SMTExprRef src, uint64_t n);

private:
  camada::SMTExprRef ptr(camada::SMTExprRef obj, camada::SMTExprRef off);
  camada::SMTExprRef bytePtr(camada::SMTExprRef p, uint64_t i);
  camada::SMTExprRef base(camada::SMTExprRef obj);
  bool hasPadding(llvm::Type *ty) const;
  void storeBytes(State &st, camada::SMTExprRef p, camada::SMTExprRef bits,
                  camada::SMTExprRef prov);
  void storeConstant(State &st, camada::SMTExprRef p, const llvm::Constant *c,
                     const std::function<camada::SMTExprRef(const llvm::Constant *)> &valueOf);

  struct Object {
    camada::SMTExprRef base, size;
  };

  camada::SMTSolver &s;
  const llvm::DataLayout &dl;
  unsigned ptrBits;
  std::vector<Object> objects; // index = object id; 0 is null
  camada::SMTExprRef bases;    // object id -> base address, as an uninterpreted array
  camada::SMTExprRef end;      // first address after the last object
  llvm::DenseMap<const llvm::GlobalValue *, camada::SMTExprRef> globals;
  unsigned fresh = 0;
};

} // namespace vereda::memory
