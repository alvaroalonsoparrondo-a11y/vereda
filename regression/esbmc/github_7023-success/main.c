int main()
{
  int a, b;

  __ESBMC_assert(a + b == b + a, "addition commutes");
  __ESBMC_assert(a * 0 == 0, "zero annihilates");
  return 0;
}
// Imported from ESBMC regression/esbmc/github_7023-success
// Needs: --result-only
// RUN: --result-only
// MODE: FUTURE
// EXPECT: ^ +PASSED .*line +5 +addition commutes$
// EXPECT: ^ +PASSED .*line +6 +zero annihilates$
// EXPECT: ^\*\* 0 of 2 properties failed, 2 passed$
// EXPECT: ^VERIFICATION SUCCESSFUL$
// EXPECT: \A(?![\s\S]*NOT CHECKED)[\s\S]*\Z
