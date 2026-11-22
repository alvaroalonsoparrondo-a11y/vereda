/* Without interval widening, y's stored interval excludes 0 after flush,
 * making the div constraint UNSAT -- a false-safe verdict. */
extern float __VERIFIER_nondet_float(void);
#include <fenv.h>

int main(void)
{
  fesetround(FE_UPWARD); /* FE_UPWARD */
  float x = __VERIFIER_nondet_float();
  __VERIFIER_assume(x > 0.0f && x < 1e-22f);
  float y = x * x; /* flushes to zero */
  float z = 1.0f / y; /* division by flushed zero yields +inf */
  __VERIFIER_assert(z < 1e30f); // result of div-by-flushed-zero must be finite
  return 0;
}
// Imported from ESBMC regression/ir-ra/ra-mul-rup-flush-then-div-fail
// Needs: --ir-ieee
// RUN: --ir-ieee --z3
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
