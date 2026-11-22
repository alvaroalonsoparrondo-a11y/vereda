// #10383: a VLA with an empty initializer is zero-initialised.
int nondet_int(void);
int main(void)
{
  int n = nondet_int();
  __VERIFIER_assume(n > 0 && n < 4);
  int a[n] = {};
  __VERIFIER_assert(a[n - 1] != 0); // nonzero
  return 0;
}
// Imported from ESBMC regression/esbmc/github_10383_fail
// Needs: --std c2x
// RUN: --std c2x
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
// EXPECT: nonzero
