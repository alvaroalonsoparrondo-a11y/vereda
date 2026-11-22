#include <fenv.h>
extern double __VERIFIER_nondet_double(void);

int main(void)
{
  fesetround(FE_UPWARD); /* ROUND_TO_PLUS_INF */
  double x = __VERIFIER_nondet_double();
  __VERIFIER_assume(x > 0.0 && x < 1e-162);
  double y = x * x; /* exact product is strictly positive and strictly
                        below min_subnormal (~4.94e-324) in magnitude */
  /* Under round-toward-+infinity, a strictly positive exact result can
   * never round down to 0.0 -- RUP always rounds a positive
   * non-representable value UP to the next representable value. */
  __VERIFIER_assert(y != 0.0); // RUP must not flush a positive tiny product to zero
  return 0;
}
// Imported from ESBMC regression/ir-ra/ra-mul-rup-tiny-product-no-flush
// Needs: --ir-ieee
// RUN: --ir-ieee --z3
// MODE: FUTURE
// EXPECT: ^VERIFICATION SUCCESSFUL$
