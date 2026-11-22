// #10383: a VLA with an empty initializer is zero-initialised.
int nondet_int(void);
int main(void)
{
  int n = nondet_int();
  __ESBMC_assume(n > 0 && n < 4);
  int a[n] = {};
  __ESBMC_assert(a[0] == 0 && a[n - 1] == 0, "zero");
  return 0;
}
// Imported from ESBMC regression/esbmc/github_10383
// Needs: --std c2x
// RUN: --std c2x
// MODE: FUTURE
// EXPECT: ^VERIFICATION SUCCESSFUL$
