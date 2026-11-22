int main()
{
  int a, b;

  __ESBMC_assert(a + b == b + a, "\t");
  __ESBMC_assert(a == 1, "P2");
  return 0;
}
// Imported from ESBMC regression/esbmc/github_7023-blank-desc
// Needs: --result-only
// RUN: --result-only
// MODE: FUTURE
// EXPECT: ^  PASSED +\[main\.assertion\.1\]  line 5[^\t\n]*$
// EXPECT: ^  FAILED +\[main\.assertion\.2\]  line 6  P2$
// EXPECT: ^\*\* 1 of 2 properties failed, 1 passed$
// EXPECT: ^VERIFICATION FAILED$
