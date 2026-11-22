#include <assert.h>

extern int __VERIFIER_nondet_int(void);

/* Under --ir-ieee, a nondet int lifted to double can be <= 0.0,
 * so the assertion must fail. */
int main(void)
{
  int n = __VERIFIER_nondet_int();
  double x = (double)n;
  assert(x > 0.0);
  return 0;
}
// Imported from ESBMC regression/ir-ra/int-to-fp
// Needs: --ir-ieee
// RUN: --ir-ieee --z3
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
