int main()
{
  int a, b, c;

  __ESBMC_assert(a + b == b + a, "A1");
  __ESBMC_assert(a + b == a + c, "A2");
}
// Imported from ESBMC regression/esbmc/github_7023-multi
// Needs: --result-only
// RUN: --result-only --multi-property
// MODE: FUTURE
// EXPECT: ^ +PASSED .*line +5 +A1$
// EXPECT: ^ +FAILED .*line +6 +A2$
// EXPECT: ^\*\* 1 of 2 properties failed, 1 passed$
// EXPECT: ^VERIFICATION FAILED$
