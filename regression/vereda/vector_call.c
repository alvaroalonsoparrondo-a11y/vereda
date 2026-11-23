// A vector passed to and returned from a function stays one value across
// the call: the elements are packed into one bitvector there.
// RUN: --unwind 2
// EXPECT: ^VERIFICATION FAILED$
// EXPECT: line 16
extern void __VERIFIER_assert(int);
extern int __VERIFIER_nondet_int(void);
typedef short v8hi __attribute__((__vector_size__(16)));
__attribute__((noinline)) static v8hi swap(v8hi v) {
  return __builtin_shufflevector(v, v, 7, 6, 5, 4, 3, 2, 1, 0);
}
int main(void) {
  v8hi v = {0, 1, 2, 3, 4, 5, 6, __VERIFIER_nondet_int()};
  v8hi w = swap(v);
  __VERIFIER_assert(w[1] == 6 && w[7] == 0);
  __VERIFIER_assert(w[0] != 9);
  return 0;
}
