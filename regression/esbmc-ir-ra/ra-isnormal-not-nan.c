#include <math.h>

#include <fenv.h>
extern double __VERIFIER_nondet_double(void);

int main(void)
{
  fesetround(FE_TONEAREST);
  double x = __VERIFIER_nondet_double();
  __VERIFIER_assume(x == 1.0);
  __VERIFIER_assert(isnormal(x)); // isnormal(1.0) is true
  return 0;
}
// Imported from ESBMC regression/ir-ra/ra-isnormal-not-nan
// Needs: --ir-ieee
// RUN: --ir-ieee --z3
// MODE: FUTURE
// EXPECT: ^VERIFICATION SUCCESSFUL$
