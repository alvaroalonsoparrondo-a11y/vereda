#include <float.h>
#include <math.h>

#include <fenv.h>
extern double __VERIFIER_nondet_double(void);

int main(void)
{
  fesetround(FE_TONEAREST); /* ROUND_TO_EVEN */
  double x = __VERIFIER_nondet_double();
  double y = __VERIFIER_nondet_double();
  /* fmod(finite, finite nonzero): well-defined, not NaN */
  __VERIFIER_assume(x > 0.0 && x < DBL_MAX);
  __VERIFIER_assume(y > 0.0 && y < DBL_MAX);
  double r = fmod(x, y);

  __VERIFIER_assert(r == r); // fmod(finite, finite) should not be NaN
  return 0;
}
// Imported from ESBMC regression/ir-ra/ra-fmod-finite-not-nan
// Needs: --ir-ieee
// RUN: --ir-ieee --z3
// MODE: FUTURE
// EXPECT: ^VERIFICATION SUCCESSFUL$
