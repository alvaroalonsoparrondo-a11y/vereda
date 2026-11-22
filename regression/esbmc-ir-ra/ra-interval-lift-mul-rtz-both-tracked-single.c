/* Regression test: RTZ (ROUND_TO_ZERO) interval lifting for ieee_mul --
 * both operands tracked, single precision.
 *
 * PURPOSE
 * -------
 * Mirrors ra-interval-lift-mul-rtz-both-tracked but exercises the
 * single-precision (float) path.
 *
 * PATTERNS CHECKED (see test.desc)
 *   ra_lo_tz::0   -- first mul's lower bound declared
 *   ra_lo_tz::1   -- second mul's lifted lower bound declared
 *   (* |smt_conv::ra_lo_tz::0|  -- endpoint product in hull
 *   (ite           -- nested ITE present
 *   8388608        -- Z3 numerator for eps_rel_dir = 2^-23 (single)
 *   ^VERIFICATION FAILED$
 */
#include <assert.h>

#include <fenv.h>
extern float __VERIFIER_nondet_float(void);

int main(void)
{
  fesetround(FE_TOWARDZERO); /* ROUND_TO_ZERO */
  float x = __VERIFIER_nondet_float();
  float y = __VERIFIER_nondet_float();
  float z = x * y; /* first RTZ mul: both fresh -> point fallback; stored */
  float w = z * z; /* second RTZ mul: both operands tracked -> full lift */

  /* Always false in real/integer encoding: w == z * z exactly. */
  assert(w != z * z);
  return 0;
}
// Imported from ESBMC regression/ir-ra/ra-interval-lift-mul-rtz-both-tracked-single
// Needs: --ir-ieee
// RUN: --ir-ieee --z3 --smt-formula-too
// MODE: FUTURE
// EXPECT: \(declare-fun \|smt_conv::ra_lo_tz::0\| \(\) Real\)
// EXPECT: \(declare-fun \|smt_conv::ra_lo_tz::1\| \(\) Real\)
// EXPECT: \(< \|smt_conv::ra_lo_tz::0\| 0
// EXPECT: \(\* \|c:ra\-interval\-lift\-mul\-rtz\-both\-tracked\-single\.c@
// EXPECT: 8388608
// EXPECT: ^VERIFICATION FAILED$
