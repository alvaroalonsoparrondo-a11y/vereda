#include <math.h>

#include <fenv.h>
extern double __VERIFIER_nondet_double(void);

int main(void)
{
  fesetround(FE_TONEAREST); /* ROUND_TO_EVEN */
  double x = __VERIFIER_nondet_double();
  double y = __VERIFIER_nondet_double();
  __VERIFIER_assume(x == 0.0);
  __VERIFIER_assume(y == 0.0);
  double z = x / y;
  double t = z + 1.0;

  __VERIFIER_assert(!(t > -100.0)); // NaN + 1.0 > -100.0 is false
  return 0;
}
// Imported from ESBMC regression/ir-ra/ra-div-zero-zero-nan-prop
// Needs: --ir-ieee
// RUN: --ir-ieee --z3
// MODE: FUTURE
// EXPECT: ^VERIFICATION SUCCESSFUL$
