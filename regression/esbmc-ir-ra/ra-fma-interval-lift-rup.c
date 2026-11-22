/* Regression test: FMA interval lifting under --ir-ieee (RUP / FE_UPWARD).
 *
 * Verifies that encode_ieee_fma takes the RUP interval-lifted path when
 * fesetround(FE_UPWARD) is used.
 *
 * x in [1, 2],  y in [3, 4],  z in [5, 6]
 * FMA hull [8, 14]; RUP enclosure: exact lower bound, upper gets B_dir error.
 * Assertion r > 100 is always false: VERIFICATION FAILED.
 *
 * Pattern ra_lo_up:: / ra_hi_up:: confirms the RUP tight path was taken.
 * Numerator 22204460492503131 is Z3's rational for eps_up = 2^-52 (double).
 */
#include <assert.h>
#include <fenv.h>
#include <math.h>

extern double __VERIFIER_nondet_double(void);

int main(void)
{
  fesetround(FE_UPWARD);
  double x = __VERIFIER_nondet_double();
  double y = __VERIFIER_nondet_double();
  double z = __VERIFIER_nondet_double();
  __ESBMC_assume(x >= 1.0 && x <= 2.0);
  __ESBMC_assume(y >= 3.0 && y <= 4.0);
  __ESBMC_assume(z >= 5.0 && z <= 6.0);

  double r = fma(x, y, z);

  assert(r > 100.0);
  return 0;
}
// Imported from ESBMC regression/ir-ra/ra-fma-interval-lift-rup
// Needs: --ir-ieee
// RUN: --ir-ieee --z3 --smt-formula-too
// MODE: FUTURE
// EXPECT: \(declare-fun \|smt_conv::ra_lo_up::[0-9]+\| \(\) Real\)
// EXPECT: \(declare-fun \|smt_conv::ra_hi_up::[0-9]+\| \(\) Real\)
// EXPECT: \(\*
// EXPECT: 22204460492503131
// EXPECT: ^VERIFICATION FAILED$
