// --interval-symex-assert: domain proves both claims from x in [5, 10].
int main()
{
  int x;
  __ESBMC_assume(x >= 5 && x <= 10);
  __ESBMC_assert(x >= 0, "x must be non-negative");
  __ESBMC_assert(x <= 100, "x must be at most 100");
  return 0;
}
// Imported from ESBMC regression/esbmc/interval_symex_assert_prune
// Needs: --interval-symex-assert
// RUN: --interval-symex-assert --multi-property
// MODE: FUTURE
// EXPECT: ^VERIFICATION SUCCESSFUL$
// EXPECT: ^Generated 2 VCC\(s\), 0 remaining after simplification
// EXPECT: ^ +PASSED .*line 6 +x must be non-negative \(interval\)$
// EXPECT: ^ +PASSED .*line 7 +x must be at most 100 \(interval\)$
