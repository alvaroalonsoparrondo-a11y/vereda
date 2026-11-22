#include <math.h>

extern int __ESBMC_rounding_mode;
extern double __VERIFIER_nondet_double(void);

int main(void)
{
  __ESBMC_rounding_mode = 0;
  double x = __VERIFIER_nondet_double();
  __ESBMC_assume(x == -1.0);
  double z = sqrt(x);
  __ESBMC_assert(!isinf(z), "isinf(sqrt(-1.0)) is false");
  return 0;
}
// Imported from ESBMC regression/ir-ra/ra-isinf-nan-sqrt
// Needs: --ir-ieee
// RUN: --ir-ieee --z3
// MODE: FUTURE
// EXPECT: ^VERIFICATION SUCCESSFUL$
