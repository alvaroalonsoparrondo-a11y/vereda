int main()
{
  unsigned x = 0;
  x = x - 1;
  __VERIFIER_assert(x < 5); // 0 - 1 is -1 under --ir
  return 0;
}
// Imported from ESBMC regression/ir-ra/github_10537_unsigned_wrap
// Needs: --ir
// RUN: --ir --z3
// MODE: FUTURE
// EXPECT: ^VERIFICATION SUCCESSFUL$
