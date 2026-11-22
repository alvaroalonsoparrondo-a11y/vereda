/* A nested product of unbounded floats under directed rounding: nonlinear in
 * the reals the integer/real encoding uses, so Z3's `smt` tactic alone reports
 * "incomplete (theory arithmetic)" and no verdict is reached at all.
 * The violation is a NaN operand, for which the equality is false. */
#include <assert.h>

#include <fenv.h>

int main(void)
{
  fesetround(FE_UPWARD); /* ROUND_TO_PLUS_INF */
  float x = nondet_float();
  float y = nondet_float();
  float z = x * y;
  float w = z * z;

  assert(w == z * z);
  return 0;
}
// Imported from ESBMC regression/floats/ir_nonlinear_nlsat_fail
// Needs: --ir-ieee
// RUN: --ir-ieee --z3
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
