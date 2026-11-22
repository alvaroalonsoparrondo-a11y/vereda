unsigned nondet_uint(void);

int main(void)
{
  unsigned n = nondet_uint();
  __ESBMC_assert(n <= 4294967295u, "an unsigned fits in 32 bits");
  return 0;
}
// Imported from ESBMC regression/ir-ra/github_10606_upper
// Needs: --ir
// RUN: --ir --z3
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
// EXPECT: ^  n = 4294967296$
