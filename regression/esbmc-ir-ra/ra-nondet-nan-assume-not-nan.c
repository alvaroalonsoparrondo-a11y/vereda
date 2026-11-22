extern double __VERIFIER_nondet_double(void);

int main(void)
{
  /* After assuming x > 0, the NaN predicate is forced false by
   * apply_nan_cmp: (NaN > 0) is false under IEEE 754 semantics, so the
   * assume eliminates the NaN case.  Self-equality must hold. */
  double x = __VERIFIER_nondet_double();
  __ESBMC_assume(x > 0.0);

  __ESBMC_assert(x == x, "nondet double constrained to > 0 is not NaN");
  return 0;
}
// Imported from ESBMC regression/ir-ra/ra-nondet-nan-assume-not-nan
// Needs: --ir-ieee
// RUN: --ir-ieee --z3
// MODE: FUTURE
// EXPECT: ^VERIFICATION SUCCESSFUL$
