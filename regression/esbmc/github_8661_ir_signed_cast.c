// #8661: under --ir a cast to a signed type was checked against [0, 2^N - 1],
// so every negative value was reported as a cast overflow.
int __VERIFIER_nondet_int();
int main(void)
{
  int x = __VERIFIER_nondet_int();
  __VERIFIER_assume(x == -1);
  long y = (long)x;
  return (int)y;
}
// Imported from ESBMC regression/esbmc/github_8661_ir_signed_cast
// Needs: --ir --overflow-check
// RUN: --ir --overflow-check --multi-property
// MODE: FUTURE
// EXPECT: ^VERIFICATION SUCCESSFUL$
