// NaN compares unequal to everything, itself included, and unordered
// comparisons hold on it; the class tests see its bits.
// RUN: --unwind 2
// EXPECT: ^VERIFICATION SUCCESSFUL$
#include <math.h>
extern void __VERIFIER_assert(int);
extern void __VERIFIER_assume(int);
extern double __VERIFIER_nondet_double(void);
int main(void) {
  double x = __VERIFIER_nondet_double();
  if (x != x) {
    __VERIFIER_assert(isnan(x) && !(x < 0) && !(x >= 0) && !isinf(x));
  } else {
    __VERIFIER_assert(!isnan(x) && (x < 0 || x >= 0));
    // glibc's isinf is -1 at minus infinity, so only its truth counts.
    __VERIFIER_assert(!!isinf(x) == (x == INFINITY || x == -INFINITY));
    __VERIFIER_assert(signbit(-fabs(x)) && !signbit(fabs(x)));
  }
  double zero = __VERIFIER_nondet_double();
  __VERIFIER_assume(zero == 0.0);
  __VERIFIER_assert(isnan(zero / zero) && isinf(1 / zero));
  return 0;
}
