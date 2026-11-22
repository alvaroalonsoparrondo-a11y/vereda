int main()
{
  unsigned a, b;

  __ESBMC_assume(a < 10);
  __ESBMC_assume(b < 10);
  __ESBMC_assert(a + b < 20, "sum stays bounded");
  __ESBMC_assert(a < 10, "a stays bounded");
  return 0;
}
// Imported from ESBMC regression/esbmc/github_7023-promote
// Needs: --result-only
// RUN: --result-only
// MODE: FUTURE
// EXPECT: ^  PASSED +\[main\.assertion\.1\] +line +7 +sum stays bounded$
// EXPECT: ^  PASSED +\[main\.assertion\.2\] +line +8 +a stays bounded$
// EXPECT: ^\*\* 0 of 2 properties failed, 2 passed$
// EXPECT: ^VERIFICATION SUCCESSFUL$
// EXPECT: \A(?![\s\S]*NOT CHECKED)[\s\S]*\Z
