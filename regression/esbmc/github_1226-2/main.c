#include <math.h>

int main()
{
  double x = nondet_float();

  __ESBMC_assume(isgreaterequal(x, 0.0));

  __ESBMC_assert(x == x, "");

  return 0;
}
// Imported from ESBMC regression/esbmc/github_1226-2
// EXPECT: ^VERIFICATION SUCCESSFUL$
