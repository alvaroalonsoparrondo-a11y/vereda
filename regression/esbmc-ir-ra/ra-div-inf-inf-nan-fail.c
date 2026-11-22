#include <float.h>
#include <math.h>

#include <fenv.h>
extern double __VERIFIER_nondet_double(void);

int main(void)
{
  fesetround(FE_TONEAREST); /* ROUND_TO_EVEN */
  double x = __VERIFIER_nondet_double();
  double y = __VERIFIER_nondet_double();
  /* both symbolic +inf */
  __VERIFIER_assume(x > DBL_MAX);
  __VERIFIER_assume(y > DBL_MAX);
  double z = x / y;

  __VERIFIER_assert(z > -100.0); // +inf / +inf > -100.0 should not hold (NaN)
  return 0;
}
// Imported from ESBMC regression/ir-ra/ra-div-inf-inf-nan-fail
// Needs: --ir-ieee
// RUN: --ir-ieee --z3
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
