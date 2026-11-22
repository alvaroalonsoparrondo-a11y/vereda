#include<math.h>

int main()
{
  double f, f2;
  // the following rely on f not being a NaN or Infinity
  __VERIFIER_assume(!isnan(f2));
  __VERIFIER_assume(!isinf(f2));
  f=f2;
  assert(0+f==-f);
}

// Imported from ESBMC regression/esbmc/github_2572_1
// Needs: --ir
// RUN: --z3 --ir
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
