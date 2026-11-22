#include <assert.h>

extern double __VERIFIER_nondet_double(void);

/* Under --ir-ieee, a nondet double cast to signed int can be <= 0,
 * so the assertion must fail. */
int main(void)
{
  double x = __VERIFIER_nondet_double();
  int n = (int)x;
  assert(n > 0);
  return 0;
}
// Imported from ESBMC regression/ir-ra/fp-to-int-signed
// Needs: --ir-ieee
// RUN: --ir-ieee --z3
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
