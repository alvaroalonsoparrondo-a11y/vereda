#include <math.h>

#include <fenv.h>
extern double __VERIFIER_nondet_double(void);

int main(void)
{
  fesetround(FE_TONEAREST);
  double x = __VERIFIER_nondet_double();
  double y = __VERIFIER_nondet_double();
  __VERIFIER_assume(x == 1.0);
  __VERIFIER_assume(y == 2.0);
  double z = x / y;
  __VERIFIER_assert(isfinite(z)); // isfinite(1.0 / 2.0) is true
  return 0;
}
// Imported from ESBMC regression/ir-ra/ra-isfinite-not-nan
// Needs: --ir-ieee
// RUN: --ir-ieee --z3
// MODE: FUTURE
// EXPECT: ^VERIFICATION SUCCESSFUL$
