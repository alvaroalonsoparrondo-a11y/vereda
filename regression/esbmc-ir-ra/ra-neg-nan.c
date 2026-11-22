#include <math.h>

#include <fenv.h>
extern double __VERIFIER_nondet_double(void);

int main(void)
{
  fesetround(FE_TONEAREST);
  double x = __VERIFIER_nondet_double();
  __VERIFIER_assume(x == -1.0);
  double y = sqrt(x);
  double z = -y;
  __VERIFIER_assert(isnan(z)); // isnan(-NaN) must be true
  return 0;
}
// Imported from ESBMC regression/ir-ra/ra-neg-nan
// Needs: --ir-ieee
// RUN: --ir-ieee --z3
// MODE: FUTURE
// EXPECT: ^VERIFICATION SUCCESSFUL$
