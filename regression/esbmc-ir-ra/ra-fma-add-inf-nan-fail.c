#include <float.h>
#include <math.h>

#include <fenv.h>
extern double __VERIFIER_nondet_double(void);

int main(void)
{
  fesetround(FE_TONEAREST); /* ROUND_TO_EVEN */
  double x = __VERIFIER_nondet_double();
  double y = __VERIFIER_nondet_double();
  double z = __VERIFIER_nondet_double();
  /* fma(+inf, +inf, -inf): product is +inf; adding -inf is invalid (NaN) */
  __VERIFIER_assume(x > DBL_MAX);
  __VERIFIER_assume(y > DBL_MAX);
  __VERIFIER_assume(z < -DBL_MAX);
  double r = fma(x, y, z);

  __VERIFIER_assert(r > -100.0); // fma(+inf, +inf, -inf) > -100.0 should not hold (NaN)
  return 0;
}
// Imported from ESBMC regression/ir-ra/ra-fma-add-inf-nan-fail
// Needs: --ir-ieee
// RUN: --ir-ieee --z3
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
