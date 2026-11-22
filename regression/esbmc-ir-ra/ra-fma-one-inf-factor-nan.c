#include <float.h>
#include <math.h>

#include <fenv.h>
extern double __VERIFIER_nondet_double(void);

int main(void)
{
  fesetround(FE_TONEAREST); /* ROUND_TO_EVEN */
  double x = __VERIFIER_nondet_double();
  double z = __VERIFIER_nondet_double();
  /* fma(+inf, 2.0, -inf): one infinite factor, finite nonzero second factor.
   * Product is +inf; adding -inf is an invalid operation (NaN). */
  __VERIFIER_assume(x > DBL_MAX);
  __VERIFIER_assume(z < -DBL_MAX);
  double r = fma(x, 2.0, z);

  __VERIFIER_assert(!(r > -100.0)); // fma(+inf, 2.0, -inf) > -100.0 is false (NaN)
  return 0;
}
// Imported from ESBMC regression/ir-ra/ra-fma-one-inf-factor-nan
// Needs: --ir-ieee
// RUN: --ir-ieee --z3
// MODE: FUTURE
// EXPECT: ^VERIFICATION SUCCESSFUL$
