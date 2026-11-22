#include <float.h>
#include <math.h>

extern int __ESBMC_rounding_mode;
extern double __VERIFIER_nondet_double(void);

int main(void)
{
  __ESBMC_rounding_mode = 0; /* ROUND_TO_EVEN */
  double x = __VERIFIER_nondet_double();
  double y = __VERIFIER_nondet_double();
  /* both symbolic +inf */
  __VERIFIER_assume(x > DBL_MAX);
  __VERIFIER_assume(y > DBL_MAX);
  double z = x / y;

  __VERIFIER_assert(!(z > -100.0)); // +inf / +inf > -100.0 is false (NaN)
  return 0;
}
// Imported from ESBMC regression/ir-ra/ra-div-inf-inf-nan
// Needs: --ir-ieee
// RUN: --ir-ieee --z3
// MODE: FUTURE
// EXPECT: ^VERIFICATION SUCCESSFUL$
