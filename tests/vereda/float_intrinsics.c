// The rounding functions, square root and fma that clang turns into LLVM
// intrinsics.
// RUN: --unwind 2
// EXPECT: ^VERIFICATION SUCCESSFUL$
extern void __VERIFIER_assert(int);
extern void __VERIFIER_assume(int);
extern double __VERIFIER_nondet_double(void);
int main(void) {
  double x = __VERIFIER_nondet_double();
  __VERIFIER_assume(x > -2.5 && x < -2.25);
  __VERIFIER_assert(__builtin_floor(x) == -3 && __builtin_ceil(x) == -2);
  __VERIFIER_assert(__builtin_trunc(x) == -2 && __builtin_round(x) == -2);
  __VERIFIER_assert(__builtin_fabs(x) == -x);
  __VERIFIER_assert(__builtin_copysign(1.0, x) == -1.0);
  __VERIFIER_assert(__builtin_fmin(x, 0.0) == x && __builtin_fmax(x, 0.0) == 0.0);
  double y = __VERIFIER_nondet_double();
  __VERIFIER_assume(y == 2.25);
  __VERIFIER_assert(__builtin_sqrt(y) == 1.5);
  __VERIFIER_assert(__builtin_fma(y, 2.0, 1.0) == 5.5);
  __VERIFIER_assert(__builtin_round(y + 0.25) == 3.0 && __builtin_rint(y + 0.25) == 2.0);
  return 0;
}
