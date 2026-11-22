extern int __ESBMC_rounding_mode;
extern double __VERIFIER_nondet_double(void);

int main(void)
{
  __ESBMC_rounding_mode = 2; /* ROUND_TO_PLUS_INF: negative tiny values flush to 0 */
  double a = __VERIFIER_nondet_double();
  double b = __VERIFIER_nondet_double();
  __VERIFIER_assume(a > 0.0 && a < 1e-162);
  __VERIFIER_assume(b > 0.5 && b < 1.5); /* symbolic, ordinary nonzero denominator */
  double y = (-a) / b; /* the division itself, not one of its operands,
                           produces the flushed negative zero */
  /* encode_ieee_div wraps its subnormal-flush result in a further ite
   * (to select the div-by-zero infinity case); the negative-zero
   * predicate mk_subnormal_flush attaches must survive that wrapping so
   * it is still visible on the division's own returned value. */
  __VERIFIER_assert(
    __signbit(y) != 0
); // a division's own flushed result must still report a negative sign bit
  return 0;
}
// Imported from ESBMC regression/ir-ra/ra-div-rup-flush-preserves-own-signbit
// Needs: --ir-ieee
// RUN: --ir-ieee --z3
// MODE: FUTURE
// EXPECT: ^VERIFICATION SUCCESSFUL$
