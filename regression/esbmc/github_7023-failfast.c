int main()
{
  int a, b, c;

  __ESBMC_assert(a == 1, "P1");
  __ESBMC_assert(b == 2, "P2");
  __ESBMC_assert(c == 3, "P3");
  return 0;
}
// Imported from ESBMC regression/esbmc/github_7023-failfast
// Needs: --result-only --multi-fail-fast 0
// RUN: --result-only --multi-property --multi-fail-fast 0
// MODE: FUTURE
// EXPECT: ^VERIFICATION SUCCESSFUL$
// EXPECT: \A(?![\s\S]*PASSED)[\s\S]*\Z
