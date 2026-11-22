// A pointer to a function without a body: the call returns any value.
// RUN: --unwind 2
// EXPECT: ^VERIFICATION FAILED$
extern void __VERIFIER_assert(int);
extern int unknown(int);
int main(void) {
  int (*f)(int) = unknown;
  __VERIFIER_assert(f(1) != 7);
  return 0;
}
