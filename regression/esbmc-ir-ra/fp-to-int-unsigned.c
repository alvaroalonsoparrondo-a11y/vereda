#include <assert.h>

extern double __VERIFIER_nondet_double(void);

/* Under --ir-ieee, a negative double cast to unsigned int is clamped to 0,
 * so the assertion must fail when x < 0. */
int main(void)
{
  double x = __VERIFIER_nondet_double();
  unsigned int n = (unsigned int)x;
  assert(n > 0);
  return 0;
}
// Imported from ESBMC regression/ir-ra/fp-to-int-unsigned
// Needs: --ir-ieee
// RUN: --ir-ieee --z3
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
