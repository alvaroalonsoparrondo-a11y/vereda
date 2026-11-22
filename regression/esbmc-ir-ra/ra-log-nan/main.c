#include <math.h>

int main(void)
{
  /* The operational model defines log of a negative argument as NaN. */
  double r = log(-1.0);
  __ESBMC_assert(r != r, "log(-1.0) must be NaN");
  return 0;
}
// Imported from ESBMC regression/ir-ra/ra-log-nan
// Needs: --ir-ieee
// RUN: --ir-ieee --z3
// MODE: FUTURE
// EXPECT: ^VERIFICATION SUCCESSFUL$
