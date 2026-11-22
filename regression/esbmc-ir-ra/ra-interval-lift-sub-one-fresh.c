/* Regression test: RNE interval lifting for ieee_sub -- one tracked, one fresh.
 *
 * PURPOSE
 * -------
 * Verifies the mixed lookup path for ieee_sub: when one operand of a second
 * RNE ieee_sub is tracked in ir_ra_interval_map and the other is a fresh
 * nondet variable, the tracked operand uses its stored interval while the
 * fresh one falls back to the point interval {side, side}.
 *
 * PROOF SHAPE (B_near, RNE, double precision)
 * -------------------------------------------
 * First sub:  z = x - y   (both fresh -> point fallback; z stored in map)
 *   ir_ra_interval_map[real_z] = {ra_lo::0, ra_hi::0}
 *
 * Second sub:  w = z - x  (z tracked, x fresh -> mixed path)
 *   iv(z) = {ra_lo::0, ra_hi::0}   (from map)
 *   iv(x) = {x_smt, x_smt}         (point fallback)
 *   L_R2 = ra_lo::0 - x_smt
 *   U_R2 = ra_hi::0 - x_smt
 *   ra_lo::1 = L_R2 - B_near(L_R2)
 *   ra_hi::1 = U_R2 + B_near(U_R2)
 *
 * PATTERNS CHECKED (see test.desc)
 * ---------------------------------
 *   ra_lo::0   -- first subtraction's interval lower bound declared
 *   ra_lo::1   -- second subtraction's mixed-path lower bound declared
 *   (ite        -- absolute value present
 *   5551115123125783  -- Z3 numerator for eps_rel = 2^-53 (double)
 *   ^VERIFICATION FAILED$  -- run completed
 */
#include <assert.h>

extern double __VERIFIER_nondet_double(void);

int main(void)
{
  double x = __VERIFIER_nondet_double();
  double y = __VERIFIER_nondet_double();
  double z = x - y;   /* first RNE sub: both fresh -> point fallback; stored */
  double w = z - x;   /* second RNE sub: z tracked, x fresh -> mixed path */

  /* Always false in real/integer encoding: w == z - x exactly. */
  assert(w != z - x);
  return 0;
}
// Imported from ESBMC regression/ir-ra/ra-interval-lift-sub-one-fresh
// Needs: --ir-ieee
// RUN: --ir-ieee --z3 --smt-formula-too
// MODE: FUTURE
// EXPECT: \(declare-fun \|smt_conv::ra_lo::0\| \(\) Real\)
// EXPECT: \(declare-fun \|smt_conv::ra_lo::1\| \(\) Real\)
// EXPECT: \(< \|smt_conv::ra_lo::0\| 0
// EXPECT: \(- \|c:ra\-interval\-lift\-sub\-one\-fresh\.c@
// EXPECT: 5551115123125783
// EXPECT: ^VERIFICATION FAILED$
