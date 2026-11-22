#include <float.h>



static inline double fabs_custom(double x)
{
  return x < 0.0 ? -x : x;
}

int main(void)
{
  double a = __VERIFIER_nondet_double();
  double b = __VERIFIER_nondet_double();
  __VERIFIER_assume(a >= -1000.0 && a <= 1000.0);
  __VERIFIER_assume(b >= -1000.0 && b <= 1000.0);
  double diff = a - b;

  __VERIFIER_assert(fabs_custom(diff) <= 1.0); // diff should stay tiny
  return 0;
}

// Imported from ESBMC regression/floats/ir_counterexample
// Needs: --ir
// RUN: --ir --no-slice
// MODE: FUTURE
// EXPECT: ^  diff = (?!0\.000000).+$
// EXPECT: ^VERIFICATION FAILED$
