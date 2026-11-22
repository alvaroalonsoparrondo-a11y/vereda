#include <math.h>

#include <fenv.h>
extern double __VERIFIER_nondet_double(void);
extern int __VERIFIER_nondet_int(void);

int main(void)
{
  fesetround(FE_TONEAREST);
  double x = __VERIFIER_nondet_double();
  __VERIFIER_assume(x == -1.0);
  double y = sqrt(x);
  int c = __VERIFIER_nondet_int();
  __VERIFIER_assume(c != 0);
  double z = c ? y : 0.0;
  __VERIFIER_assert(!isnan(z)); // true branch NaN: z must not be NaN
  return 0;
}
// Imported from ESBMC regression/ir-ra/ra-ite-nan-true-fail
// Needs: --ir-ieee
// RUN: --ir-ieee --z3
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
