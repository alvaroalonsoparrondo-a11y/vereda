/* Regression test: RNE interval lifting for ieee_sub -- both operands fresh,
 * single precision (zero-regression sentinel).
 *
 * PURPOSE
 * -------
 * Mirrors ra-interval-lift-sub-both-fresh but exercises the single-precision
 * (float) path. Verifies that when both operands are fresh nondet variables,
 * the point-interval fallback collapses to the single-step RNE formula with
 * single-precision epsilon constants.
 *
 * PROOF SHAPE (point-interval fallback, single precision)
 * -------------------------------------------------------
 * Both x and y are fresh; lo_r == hi_r == real_z, producing:
 *   ra_lo = real_z - B_near(real_z)   [eps_rel = 2^-24]
 *   ra_hi = real_z + B_near(real_z)
 *
 * PATTERNS CHECKED (see test.desc)
 * ---------------------------------
 *   ra_lo::          -- tight RNE path taken
 *   ra_hi::          -- tight RNE path taken
 *   (ite             -- |r| absolute value present
 *   5960464477539063 -- Z3 numerator for eps_rel = 2^-24 (single)
 *   ^VERIFICATION FAILED$  -- run completed
 */
#include <assert.h>

extern float __VERIFIER_nondet_float(void);

int main(void)
{
  float x = __VERIFIER_nondet_float();
  float y = __VERIFIER_nondet_float();
  float z = x - y;   /* both operands fresh -> point fallback -> single-step equivalent */

  /* Always false in real/integer encoding: z == x - y exactly. */
  assert(z != x - y);
  return 0;
}
// Imported from ESBMC regression/ir-ra/ra-interval-lift-sub-both-fresh-single
// Needs: --ir-ieee
// RUN: --ir-ieee --z3 --smt-formula-too
// MODE: FUTURE
// EXPECT: \(declare-fun \|smt_conv::ra_lo::[0-9]+\| \(\) Real\)
// EXPECT: \(declare-fun \|smt_conv::ra_hi::[0-9]+\| \(\) Real\)
// EXPECT: \(ite
// EXPECT: 5960464477539063
// EXPECT: ^VERIFICATION FAILED$
