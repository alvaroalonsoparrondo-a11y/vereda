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
  /* fma(+inf, +inf, +inf) = +inf: same-sign infinite addend, not NaN */
  __VERIFIER_assume(x > DBL_MAX);
  __VERIFIER_assume(y > DBL_MAX);
  __VERIFIER_assume(z > DBL_MAX);
  double r = fma(x, y, z);

  __VERIFIER_assert(r > DBL_MAX); // fma(+inf, +inf, +inf) should be +inf
  return 0;
}
// Imported from ESBMC regression/ir-ra/ra-fma-add-inf-not-nan
// Needs: --ir-ieee
// RUN: --ir-ieee --z3
// MODE: FUTURE
// EXPECT: ^VERIFICATION SUCCESSFUL$
