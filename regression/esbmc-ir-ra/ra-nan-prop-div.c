#include <math.h>

int main(void)
{
  double s = sqrt(-1.0);
  double t = s / 2.0;
  __VERIFIER_assert(!(t < 100.0)); // NaN / 2.0 < 100.0 is false
  __VERIFIER_assert(t != t); // NaN / 2.0 != itself
  return 0;
}
// Imported from ESBMC regression/ir-ra/ra-nan-prop-div
// Needs: --ir-ieee
// RUN: --ir-ieee --z3
// MODE: FUTURE
// EXPECT: ^VERIFICATION SUCCESSFUL$
