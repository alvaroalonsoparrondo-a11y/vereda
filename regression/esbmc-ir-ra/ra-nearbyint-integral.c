/* Already-integral input: nearbyint(3.0) == 3.0 under any rounding mode */
#include <math.h>

extern int __ESBMC_rounding_mode;
extern double __VERIFIER_nondet_double(void);

int main(void)
{
  __ESBMC_rounding_mode = 0; /* ROUND_TO_EVEN */
  double x = __VERIFIER_nondet_double();
  __VERIFIER_assume(x == 3.0);
  double y = nearbyint(x);
  __VERIFIER_assert(y == 3.0); // nearbyint of an integer returns that integer
  return 0;
}
// Imported from ESBMC regression/ir-ra/ra-nearbyint-integral
// Needs: --ir-ieee
// RUN: --ir-ieee --z3
// MODE: FUTURE
// EXPECT: ^VERIFICATION SUCCESSFUL$
