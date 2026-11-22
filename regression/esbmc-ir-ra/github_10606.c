unsigned nondet_uint(void);

int main(void)
{
  unsigned n = nondet_uint();
  __VERIFIER_assert(n >= 0); // an unsigned is never negative
  return 0;
}
// Imported from ESBMC regression/ir-ra/github_10606
// Needs: --ir
// RUN: --ir --z3
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
// EXPECT: ^  n = -1$
