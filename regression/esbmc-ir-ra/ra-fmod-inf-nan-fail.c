#include <float.h>
#include <math.h>

extern int __ESBMC_rounding_mode;
extern double __VERIFIER_nondet_double(void);

int main(void)
{
  __ESBMC_rounding_mode = 0; /* ROUND_TO_EVEN */
  double x = __VERIFIER_nondet_double();
  double y = __VERIFIER_nondet_double();
  /* fmod(+inf, finite): infinite dividend is an invalid operation (NaN) */
  __VERIFIER_assume(x > DBL_MAX);
  __VERIFIER_assume(y > 0.0 && y < DBL_MAX);
  double r = fmod(x, y);

  __VERIFIER_assert(r > -100.0); // fmod(+inf, finite) > -100.0 should not hold (NaN)
  return 0;
}
// Imported from ESBMC regression/ir-ra/ra-fmod-inf-nan-fail
// Needs: --ir-ieee
// RUN: --ir-ieee --z3
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
