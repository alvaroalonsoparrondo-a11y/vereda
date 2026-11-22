/* Regression test: RUP (ROUND_TO_PLUS_INF) interval lifting for ieee_mul --
 * one tracked, one fresh, single precision.
 *
 * PURPOSE
 * -------
 * Mirrors ra-interval-lift-mul-rup-one-fresh but exercises the
 * single-precision (float) path.
 *
 * PROOF SHAPE (B_dir, RUP, single precision)
 * ------------------------------------------
 * Second mul:  w = z * x  (z tracked, x fresh -> mixed path)
 *   lo_r = min(ra_lo_up::0 * x_smt, ra_hi_up::0 * x_smt)
 *   hi_r = max(ra_lo_up::0 * x_smt, ra_hi_up::0 * x_smt)
 *   ra_lo_up::1 = lo_r,  ra_hi_up::1 = hi_r + B_dir(hi_r)  [single eps]
 *
 * PATTERNS CHECKED (see test.desc)
 *   ra_lo_up::0   -- first mul's lower bound declared
 *   ra_lo_up::1   -- second mul's mixed-path lower bound declared
 *   (* |smt_conv::ra_lo_up::0|  -- tracked endpoint in hull product
 *   (ite           -- nested ITE present
 *   8388608        -- Z3 numerator for eps_rel_dir = 2^-23 (single)
 *   ^VERIFICATION FAILED$
 */
#include <assert.h>

#include <fenv.h>
extern float __VERIFIER_nondet_float(void);

int main(void)
{
  fesetround(FE_UPWARD); /* ROUND_TO_PLUS_INF */
  float x = __VERIFIER_nondet_float();
  float y = __VERIFIER_nondet_float();
  float z = x * y; /* first RUP mul: both fresh -> point fallback; stored */
  float w = z * x; /* second RUP mul: z tracked, x fresh -> mixed path */

  /* Always false in real/integer encoding: w == z * x exactly. */
  assert(w != z * x);
  return 0;
}
// Imported from ESBMC regression/ir-ra/ra-interval-lift-mul-rup-one-fresh-single
// Needs: --ir-ieee
// RUN: --ir-ieee --z3 --smt-formula-too
// MODE: FUTURE
// EXPECT: \(declare-fun \|smt_conv::ra_lo_up::0\| \(\) Real\)
// EXPECT: \(declare-fun \|smt_conv::ra_lo_up::1\| \(\) Real\)
// EXPECT: \(< \|smt_conv::ra_lo_up::0\| 0
// EXPECT: \(\* \|c:ra\-interval\-lift\-mul\-rup\-one\-fresh\-single\.c@
// EXPECT: (8388608|\(/ 1\.0 0\.0\))
// EXPECT: Solving with solver Z3
