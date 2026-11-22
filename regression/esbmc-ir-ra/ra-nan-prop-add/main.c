#include <math.h>

int main(void)
{
  double s = sqrt(-1.0);
  double t = s + 1.0;
  __ESBMC_assert(!(t < 100.0), "NaN + 1.0 < 100.0 is false");
  __ESBMC_assert(t != t, "NaN + 1.0 != itself");
  return 0;
}
// Imported from ESBMC regression/ir-ra/ra-nan-prop-add
// Needs: --ir-ieee
// RUN: --ir-ieee --z3
// MODE: FUTURE
// EXPECT: ^VERIFICATION SUCCESSFUL$
