#include <math.h>

extern int __ESBMC_rounding_mode;
extern double __VERIFIER_nondet_double(void);

int main(void)
{
  __ESBMC_rounding_mode = 0;
  double x = __VERIFIER_nondet_double();
  __VERIFIER_assume(x == -1.0);
  double y = sqrt(x);
  double z = fabs(y);
  __VERIFIER_assert(isnan(z)); // isnan(fabs(NaN)) must be true
  return 0;
}
// Imported from ESBMC regression/ir-ra/ra-fabs-nan
// Needs: --ir-ieee
// RUN: --ir-ieee --z3
// MODE: FUTURE
// EXPECT: ^VERIFICATION SUCCESSFUL$
