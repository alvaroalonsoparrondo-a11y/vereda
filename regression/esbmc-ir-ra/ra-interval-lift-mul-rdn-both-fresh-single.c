/* Regression test: RDN (ROUND_TO_MINUS_INF) interval lifting for ieee_mul --
 * both operands fresh, single precision.
 *
 * PURPOSE
 * -------
 * Mirrors ra-interval-lift-mul-rdn-both-fresh but exercises the
 * single-precision (float) path.
 *
 * PROOF SHAPE (point-interval fallback, single precision RDN)
 * -----------------------------------------------------------
 * EbRDN([R,R]) = [R - B_dir(R), R], B_dir uses eps_rel_dir = 2^-23 (single).
 *
 * PATTERNS CHECKED (see test.desc)
 *   ra_lo_dn::   -- RDN tight path taken
 *   ra_hi_dn::   -- RDN tight path taken
 *   (ite          -- |r| absolute value in B_dir computation
 *   8388608       -- Z3 numerator for eps_rel_dir = 2^-23 (single)
 *   ^VERIFICATION FAILED$
 */
#include <assert.h>

#include <fenv.h>
extern float __VERIFIER_nondet_float(void);

int main(void)
{
  fesetround(FE_DOWNWARD); /* ROUND_TO_MINUS_INF */
  float x = __VERIFIER_nondet_float();
  float y = __VERIFIER_nondet_float();
  float z = x * y; /* both fresh -> point fallback */

  /* Always false in real/integer encoding: z == x * y exactly. */
  assert(z != x * y);
  return 0;
}
// Imported from ESBMC regression/ir-ra/ra-interval-lift-mul-rdn-both-fresh-single
// Needs: --ir-ieee
// RUN: --ir-ieee --z3 --smt-formula-too
// MODE: FUTURE
// EXPECT: \(declare-fun \|smt_conv::ra_lo_dn::[0-9]+\| \(\) Real\)
// EXPECT: \(declare-fun \|smt_conv::ra_hi_dn::[0-9]+\| \(\) Real\)
// EXPECT: \(ite
// EXPECT: 8388608
// EXPECT: ^VERIFICATION FAILED$
