/* RTE tie at 2.5: floor=2 (even) so stay at 2 */
#include <math.h>

#include <fenv.h>
extern double __VERIFIER_nondet_double(void);

int main(void)
{
  fesetround(FE_TONEAREST); /* ROUND_TO_EVEN */
  double x = __VERIFIER_nondet_double();
  __VERIFIER_assume(x == 2.5);
  double y = nearbyint(x);
  __VERIFIER_assert(y == 2.0); // RTE tie at 2.5 rounds to 2
  return 0;
}
// Imported from ESBMC regression/ir-ra/ra-nearbyint-rte-tie-25
// Needs: --ir-ieee
// RUN: --ir-ieee --z3
// MODE: FUTURE
// EXPECT: ^VERIFICATION SUCCESSFUL$
