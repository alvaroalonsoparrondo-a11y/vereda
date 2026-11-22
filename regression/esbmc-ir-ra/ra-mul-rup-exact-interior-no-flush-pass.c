#include <fenv.h>
extern double __VERIFIER_nondet_double(void);

int main(void)
{
  fesetround(FE_UPWARD); /* ROUND_TO_PLUS_INF */
  double a = __VERIFIER_nondet_double();
  double b = __VERIFIER_nondet_double();
  /* a*b == 2^-1075, exactly -- strictly between 0 and min_subnormal
   * (2^-1074). */
  __VERIFIER_assume(a == 0x1p-537 && b == 0x1p-538);
  double y = a * b;
  /* IEEE 754 RUP always rounds a strictly positive non-representable
   * value UP (away from zero, toward +min_subnormal) -- never down to 0.
   * IR-IEEE does not quantize to the exact subnormal grid here; this test
   * checks only that the result is not flushed to zero. */
  __VERIFIER_assert(
    y != 0.0
); // RUP must not flush a positive value strictly below min_subnormal
  return 0;
}
// Imported from ESBMC regression/ir-ra/ra-mul-rup-exact-interior-no-flush-pass
// Needs: --ir-ieee
// RUN: --ir-ieee --z3
// MODE: FUTURE
// EXPECT: ^VERIFICATION SUCCESSFUL$
