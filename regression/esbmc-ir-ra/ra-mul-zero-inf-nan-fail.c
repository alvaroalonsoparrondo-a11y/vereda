#include <float.h>
#include <math.h>

extern int __ESBMC_rounding_mode;
extern double __VERIFIER_nondet_double(void);

int main(void)
{
  __ESBMC_rounding_mode = 0; /* ROUND_TO_EVEN */
  double x = __VERIFIER_nondet_double();
  double y = __VERIFIER_nondet_double();
  /* x is 0, y is symbolic +inf */
  __VERIFIER_assume(x == 0.0);
  __VERIFIER_assume(y > DBL_MAX);
  double z = x * y;

  __VERIFIER_assert(z > -100.0); // 0 * +inf > -100.0 should not hold (NaN)
  return 0;
}
// Imported from ESBMC regression/ir-ra/ra-mul-zero-inf-nan-fail
// Needs: --ir-ieee
// RUN: --ir-ieee --z3
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
