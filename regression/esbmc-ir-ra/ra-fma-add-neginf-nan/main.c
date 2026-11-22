#include <float.h>
#include <math.h>

extern int __ESBMC_rounding_mode;
extern double __VERIFIER_nondet_double(void);

int main(void)
{
  __ESBMC_rounding_mode = 0; /* ROUND_TO_EVEN */
  double x = __VERIFIER_nondet_double();
  double y = __VERIFIER_nondet_double();
  double z = __VERIFIER_nondet_double();
  /* fma(+inf, -inf, +inf): product is -inf; adding +inf is invalid (NaN) */
  __ESBMC_assume(x > DBL_MAX);
  __ESBMC_assume(y < -DBL_MAX);
  __ESBMC_assume(z > DBL_MAX);
  double r = fma(x, y, z);

  __ESBMC_assert(!(r > -100.0), "fma(+inf, -inf, +inf) > -100.0 is false (NaN)");
  return 0;
}
// Imported from ESBMC regression/ir-ra/ra-fma-add-neginf-nan
// Needs: --ir-ieee
// RUN: --ir-ieee --z3
// MODE: FUTURE
// EXPECT: ^VERIFICATION SUCCESSFUL$
