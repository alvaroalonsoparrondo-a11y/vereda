extern unsigned __VERIFIER_nondet_uint(void);
int main(void)
{
  unsigned x = __VERIFIER_nondet_uint();
  unsigned i = 0;
  __ESBMC_loop_invariant(i <= 3 && x + 1 > x);
  while (i < 3)
    i++;
  return 0;
}
// Imported from ESBMC regression/esbmc/github_10853_int_encoding
// Needs: --loop-invariant-check --ir --witness-output-yaml -
// RUN: --loop-invariant-check --ir --witness-output-yaml -
// MODE: FUTURE
// EXPECT: ^VERIFICATION SUCCESSFUL$
// EXPECT: ^  content:\n    \[\]$
