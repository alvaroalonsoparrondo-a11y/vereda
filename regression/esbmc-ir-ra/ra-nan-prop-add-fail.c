#include <math.h>

int main(void)
{
  double s = sqrt(-1.0);
  double t = s + 1.0;
  __VERIFIER_assert(t == t); // NaN + 1.0 == itself
  return 0;
}
// Imported from ESBMC regression/ir-ra/ra-nan-prop-add-fail
// Needs: --ir-ieee
// RUN: --ir-ieee --z3
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
