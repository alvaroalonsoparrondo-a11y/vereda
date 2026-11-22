#include <math.h>

extern int __ESBMC_rounding_mode;
extern double __VERIFIER_nondet_double(void);
extern int __VERIFIER_nondet_int(void);

int main(void)
{
  __ESBMC_rounding_mode = 0;
  double x = __VERIFIER_nondet_double();
  __VERIFIER_assume(x == -1.0);
  double y = sqrt(x);
  int c = __VERIFIER_nondet_int();
  __VERIFIER_assume(c < 0);
  double z = (c > 0) ? 0.0 : y;
  __VERIFIER_assert(isnan(z)); // false branch NaN: z must be NaN
  return 0;
}
// Imported from ESBMC regression/ir-ra/ra-ite-nan-false
// Needs: --ir-ieee
// RUN: --ir-ieee --z3
// MODE: FUTURE
// EXPECT: ^VERIFICATION SUCCESSFUL$
