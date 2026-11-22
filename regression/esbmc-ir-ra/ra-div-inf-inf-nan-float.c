#include <math.h>

#include <fenv.h>
extern float __VERIFIER_nondet_float(void);

int main(void)
{
  fesetround(FE_TONEAREST); /* ROUND_TO_EVEN */
  float x = __VERIFIER_nondet_float();
  __VERIFIER_assume(isinf(x));
  float y = __VERIFIER_nondet_float();
  __VERIFIER_assume(isinf(y));
  float z = x / y;

  __VERIFIER_assert(isnan(z)); // isinf(x) && isinf(y) implies isnan(x / y)
  return 0;
}
// Imported from ESBMC regression/ir-ra/ra-div-inf-inf-nan-float
// Needs: --ir-ieee
// RUN: --ir-ieee --z3
// MODE: FUTURE
// EXPECT: ^VERIFICATION SUCCESSFUL$
