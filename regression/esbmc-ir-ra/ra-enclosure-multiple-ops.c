#include <assert.h>

extern double __VERIFIER_nondet_double(void);

int main(void)
{
  double a = __VERIFIER_nondet_double();
  double b = __VERIFIER_nondet_double();
  double c = __VERIFIER_nondet_double();

  double x = a + b;
  double y = x + c;

  assert(y > x);
  return 0;
}
// Imported from ESBMC regression/ir-ra/ra-enclosure-multiple-ops
// Needs: --ir-ieee
// RUN: --ir-ieee --z3
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
