#include <math.h>

extern int __ESBMC_rounding_mode;
extern double __VERIFIER_nondet_double(void);

int main(void)
{
  __ESBMC_rounding_mode = 0;
  double x = __VERIFIER_nondet_double();
  __ESBMC_assume(x == -1.0);
  double y = sqrt(x);
  double z = -y;
  __ESBMC_assert(!isnan(z), "isnan(-NaN) must be false");
  return 0;
}
// Imported from ESBMC regression/ir-ra/ra-neg-nan-fail
// Needs: --ir-ieee
// RUN: --ir-ieee --z3
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
