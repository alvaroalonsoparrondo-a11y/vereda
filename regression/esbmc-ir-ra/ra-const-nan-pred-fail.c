int main(void)
{
  /* __builtin_nan("0") folds to a constant_floatbv NaN in the GOTO IR.
   * Asserting n > 0.0 must fail: NaN makes ordered comparisons return false. */
  double n = __builtin_nan("0");

  __VERIFIER_assert(n > 0.0); // NaN > 0.0 should not hold
  return 0;
}
// Imported from ESBMC regression/ir-ra/ra-const-nan-pred-fail
// Needs: --ir-ieee
// RUN: --ir-ieee --z3
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
