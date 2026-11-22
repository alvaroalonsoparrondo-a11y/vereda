/* RTP (round toward +inf): x in (0,1) -> 1 */
#include <math.h>

#include <fenv.h>
extern double __VERIFIER_nondet_double(void);

int main(void)
{
  fesetround(FE_UPWARD); /* ROUND_TO_PLUS_INF */
  double x = __VERIFIER_nondet_double();
  __VERIFIER_assume(x > 0.0 && x < 1.0);
  double y = nearbyint(x);
  __VERIFIER_assert(y == 1.0); // RTP: nearbyint of (0,1) is 1
  return 0;
}
// Imported from ESBMC regression/ir-ra/ra-nearbyint-rtp-pos
// Needs: --ir-ieee
// RUN: --ir-ieee --z3
// MODE: FUTURE
// EXPECT: ^VERIFICATION SUCCESSFUL$
