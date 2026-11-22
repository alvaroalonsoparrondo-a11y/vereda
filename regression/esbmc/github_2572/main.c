#include<math.h>

int main()
{
  double f, f2;
  // the following rely on f not being a NaN or Infinity
  __ESBMC_assume(!isnan(f2));
  __ESBMC_assume(!isinf(f2));
  f=f2;
  assert(0+f==f);
}

// Imported from ESBMC regression/esbmc/github_2572
// Needs: --ir-ieee
// RUN: --z3 --ir-ieee
// MODE: FUTURE
// EXPECT: ^VERIFICATION SUCCESSFUL$
