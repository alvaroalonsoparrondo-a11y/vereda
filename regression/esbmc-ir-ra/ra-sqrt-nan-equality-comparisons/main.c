#include <math.h>

int main(void)
{
  double s = sqrt(-1.0);
  __ESBMC_assert(!(s == s), "NaN == NaN is false");
  __ESBMC_assert(s != s, "NaN != NaN is true");
  return 0;
}
// Imported from ESBMC regression/ir-ra/ra-sqrt-nan-equality-comparisons
// Needs: --ir-ieee
// RUN: --ir-ieee --z3
// MODE: FUTURE
// EXPECT: ^VERIFICATION SUCCESSFUL$
