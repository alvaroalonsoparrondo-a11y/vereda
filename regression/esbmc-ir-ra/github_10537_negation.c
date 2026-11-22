int main()
{
  int x = -2147483647 - 1;
  x = -x;
  __VERIFIER_assert(x > 0); // -INT_MIN is 2^31 under --ir
  return 0;
}
// Imported from ESBMC regression/ir-ra/github_10537_negation
// Needs: --ir
// RUN: --ir --z3
// MODE: FUTURE
// EXPECT: ^VERIFICATION SUCCESSFUL$
