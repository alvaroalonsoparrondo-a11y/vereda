#include <math.h>

int main(void)
{
  double s = sqrt(-1.0);
  double t = sqrt(s);
  __VERIFIER_assert(t == t); // sqrt(NaN) == itself
  return 0;
}
// Imported from ESBMC regression/ir-ra/ra-sqrt-of-nan-fail
// Needs: --ir-ieee
// RUN: --ir-ieee --z3
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
