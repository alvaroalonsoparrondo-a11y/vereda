#include <math.h>

int main(void)
{
  double s = sqrt(-1.0);
  __VERIFIER_assert(!(s < 100.0)); // NaN < 100.0 is false
  __VERIFIER_assert(!(s <= 100.0)); // NaN <= 100.0 is false
  __VERIFIER_assert(!(s > -100.0)); // NaN > -100.0 is false
  __VERIFIER_assert(!(s >= -100.0)); // NaN >= -100.0 is false
  return 0;
}
// Imported from ESBMC regression/ir-ra/ra-sqrt-nan-ordered-comparisons
// Needs: --ir-ieee
// RUN: --ir-ieee --z3
// MODE: FUTURE
// EXPECT: ^VERIFICATION SUCCESSFUL$
