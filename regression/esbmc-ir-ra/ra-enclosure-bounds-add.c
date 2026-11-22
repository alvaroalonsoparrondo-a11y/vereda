/* Regression: --ir-ieee should process a double-precision addition through the
 * enclosure path. The assertion is intentionally false so ESBMC produces a
 * counterexample and exercises the encoding. */
#include <assert.h>

extern double __VERIFIER_nondet_double(void);

int main(void)
{
  double x = __VERIFIER_nondet_double();
  double y = __VERIFIER_nondet_double();
  double z = x + y;

  /* This is always falsifiable: x=1, y=0 gives z=1 which is not > 2. */
  assert(z > x + y + 1.0);
  return 0;
}
// Imported from ESBMC regression/ir-ra/ra-enclosure-bounds-add
// Needs: --ir-ieee
// RUN: --ir-ieee --z3
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
