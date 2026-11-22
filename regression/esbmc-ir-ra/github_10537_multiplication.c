int main()
{
  int x = 65536;
  x = x * 65536;
  __VERIFIER_assert(x != 0); // 2^16 * 2^16 is 2^32 under --ir
  return 0;
}
// Imported from ESBMC regression/ir-ra/github_10537_multiplication
// Needs: --ir
// RUN: --ir --z3
// MODE: FUTURE
// EXPECT: ^VERIFICATION SUCCESSFUL$
