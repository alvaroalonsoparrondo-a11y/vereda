#include <math.h>

extern int __ESBMC_rounding_mode;
extern double __VERIFIER_nondet_double(void);

int main(void)
{
  __ESBMC_rounding_mode = 0; /* ROUND_TO_EVEN */
  double x = __VERIFIER_nondet_double();
  double y = __VERIFIER_nondet_double();
  __VERIFIER_assume(x == 0.0);
  __VERIFIER_assume(y == 0.0);
  double z = x / y;

  __VERIFIER_assert(!(z > -100.0)); // 0.0 / 0.0 > -100.0 is false
  return 0;
}
// Imported from ESBMC regression/ir-ra/ra-div-zero-zero-nan
// Needs: --ir-ieee
// RUN: --ir-ieee --z3
// MODE: FUTURE
// EXPECT: ^VERIFICATION SUCCESSFUL$
