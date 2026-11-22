#include <float.h>
#include <math.h>

#include <fenv.h>
extern double __VERIFIER_nondet_double(void);

int main(void)
{
  fesetround(FE_TONEAREST); /* ROUND_TO_EVEN */
  double z = __VERIFIER_nondet_double();
  /* fma(DBL_MAX, 2.0, -inf): both factors finite; no invalid operation.
   * The result is not NaN, so asserting r != r (self-inequality) must fail. */
  __VERIFIER_assume(z < -DBL_MAX);
  double r = fma(DBL_MAX, 2.0, z);

  __VERIFIER_assert(r != r); // fma(DBL_MAX, 2.0, -inf) != itself should not hold (not NaN)
  return 0;
}
// Imported from ESBMC regression/ir-ra/ra-fma-finite-overflow-not-nan-fail
// Needs: --ir-ieee
// RUN: --ir-ieee --z3
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
