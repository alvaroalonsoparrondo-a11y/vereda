// A float too large to change when 1 is added: the solver must find one.
// RUN: --unwind 2
// EXPECT: ^VERIFICATION FAILED$
// EXPECT: line 12
extern void __VERIFIER_assert(int);
extern void __VERIFIER_assume(int);
extern float __VERIFIER_nondet_float(void);
int main(void) {
  float x = __VERIFIER_nondet_float();
  __VERIFIER_assume(x > 0 && x < 1e30f);
  float y = x + 1.0f;
  __VERIFIER_assert(y != x);
  return 0;
}
