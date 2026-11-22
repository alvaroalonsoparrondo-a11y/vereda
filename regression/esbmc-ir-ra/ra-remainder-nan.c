#include <math.h>

int main(void)
{
  /* The operational model defines remainder(±inf, y) as NaN. */
  double r = remainder(INFINITY, 1.0);
  __VERIFIER_assert(r != r); // remainder(INFINITY, 1.0) must be NaN
  return 0;
}
// Imported from ESBMC regression/ir-ra/ra-remainder-nan
// Needs: --ir-ieee
// RUN: --ir-ieee --z3
// MODE: FUTURE
// EXPECT: ^VERIFICATION SUCCESSFUL$
