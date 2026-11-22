#include <assert.h>
#include <math.h>
double __VERIFIER_nondet_double(void);
int main(void)
{
  double d = __VERIFIER_nondet_double();
  __VERIFIER_assume(d == 0.0);
  double e = -d;
  assert(signbit(e) == signbit(-d));
  return 0;
}
// Imported from ESBMC regression/floats/signbit_neg_ir
// Needs: --ir
// RUN: --ir
// MODE: FUTURE
// EXPECT: ^VERIFICATION SUCCESSFUL$
