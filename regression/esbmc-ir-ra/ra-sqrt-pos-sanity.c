#include <math.h>

int main(void)
{
  double s = sqrt(4.0);
  __VERIFIER_assert(s == 2.0); // sqrt(4.0) == 2.0
  __VERIFIER_assert(s == s); // positive sqrt result equals itself
  return 0;
}
// Imported from ESBMC regression/ir-ra/ra-sqrt-pos-sanity
// Needs: --ir-ieee
// RUN: --ir-ieee --z3
// MODE: FUTURE
// EXPECT: ^VERIFICATION SUCCESSFUL$
