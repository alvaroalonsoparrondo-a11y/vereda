int main()
{
  long long y = 4294967296LL;
  int x = (int)y;
  __ESBMC_assert(x != 0, "an integer cast is the identity under --ir");
  return 0;
}
// Imported from ESBMC regression/ir-ra/github_10537_narrowing_cast
// Needs: --ir
// RUN: --ir --z3
// MODE: FUTURE
// EXPECT: ^VERIFICATION SUCCESSFUL$
