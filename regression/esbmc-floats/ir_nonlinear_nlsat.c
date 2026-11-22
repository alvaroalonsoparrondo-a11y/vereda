/* Companion to ir_nonlinear_nlsat_fail: the same nonlinear goal with the NaN
 * operands assumed away, so the equality holds and the nonlinear fallback must
 * not manufacture a counterexample. */
#include <assert.h>

#include <fenv.h>

int main(void)
{
  fesetround(FE_UPWARD); /* ROUND_TO_PLUS_INF */
  float x = __VERIFIER_nondet_float();
  float y = __VERIFIER_nondet_float();
  float z = x * y;
  float w = z * z;

  __VERIFIER_assume(z == z && w == w);

  assert(w == z * z);
  return 0;
}
// Imported from ESBMC regression/floats/ir_nonlinear_nlsat
// Needs: --ir-ieee
// RUN: --ir-ieee --z3
// MODE: FUTURE
// EXPECT: ^VERIFICATION SUCCESSFUL$
