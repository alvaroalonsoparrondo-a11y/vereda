#include <math.h>

extern int __ESBMC_rounding_mode;
extern double __VERIFIER_nondet_double(void);

int main(void)
{
  __ESBMC_rounding_mode = 0; /* ROUND_TO_EVEN */
  double x = __VERIFIER_nondet_double();
  __VERIFIER_assume(x == -1.0);
  double z = sqrt(x);

  __VERIFIER_assert(isnan(z)); // isnan(sqrt(-1.0)) is true
  return 0;
}
// Imported from ESBMC regression/ir-ra/ra-isnan-sqrt-neg
// Needs: --ir-ieee
// RUN: --ir-ieee --z3
// MODE: FUTURE
// EXPECT: ^VERIFICATION SUCCESSFUL$
