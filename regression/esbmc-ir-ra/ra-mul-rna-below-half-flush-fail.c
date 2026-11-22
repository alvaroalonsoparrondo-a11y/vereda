extern int __ESBMC_rounding_mode;
extern double __VERIFIER_nondet_double(void);

int main(void)
{
  __ESBMC_rounding_mode = 1; /* ROUND_TO_AWAY */
  double x = __VERIFIER_nondet_double();
  __VERIFIER_assume(x > 0.0 && x < 1e-162);
  double y = x * x; /* exact product lands strictly below
                        min_subnormal/2 (~2.47e-324) */
  /* Ties-away: values strictly below the half-subnormal boundary correctly
   * flush to zero -- this must keep holding after the rounding-mode fix,
   * so this assertion is expected to be violated (VERIFICATION FAILED). */
  __VERIFIER_assert(
    y != 0.0
); // value below the half-subnormal boundary underflows to zero under RNA
  return 0;
}
// Imported from ESBMC regression/ir-ra/ra-mul-rna-below-half-flush-fail
// Needs: --ir-ieee
// RUN: --ir-ieee --z3
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
