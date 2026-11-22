int main(void)
{
  /* __builtin_nan("0") folds to a constant_floatbv NaN in the GOTO IR,
   * exercising the constant-NaN path in convert_terminal under --ir-ieee.
   * All ordered comparisons on NaN return false. */
  double n = __builtin_nan("0");

  __VERIFIER_assert(!(n > 0.0)); // NaN > 0.0 is false
  __VERIFIER_assert(!(n < 0.0)); // NaN < 0.0 is false
  __VERIFIER_assert(!(n == 0.0)); // NaN == 0.0 is false
  return 0;
}
// Imported from ESBMC regression/ir-ra/ra-const-nan-pred
// Needs: --ir-ieee
// RUN: --ir-ieee --z3
// MODE: FUTURE
// EXPECT: ^VERIFICATION SUCCESSFUL$
