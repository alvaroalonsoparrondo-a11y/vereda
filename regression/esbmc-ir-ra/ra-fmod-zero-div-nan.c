#include <float.h>
#include <math.h>

#include <fenv.h>
extern double __VERIFIER_nondet_double(void);

int main(void)
{
  fesetround(FE_TONEAREST); /* ROUND_TO_EVEN */
  double x = __VERIFIER_nondet_double();
  /* fmod(x, 0): zero divisor is an invalid operation (NaN) */
  __VERIFIER_assume(x > 0.0 && x < DBL_MAX);
  double r = fmod(x, 0.0);

  __VERIFIER_assert(!(r > -100.0)); // fmod(finite, 0) > -100.0 is false (NaN)
  return 0;
}
// Imported from ESBMC regression/ir-ra/ra-fmod-zero-div-nan
// Needs: --ir-ieee
// RUN: --ir-ieee --z3
// MODE: FUTURE
// EXPECT: ^VERIFICATION SUCCESSFUL$
