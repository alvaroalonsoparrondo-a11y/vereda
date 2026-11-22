int main()
{
  int x = 2147483647;
  x = x + 1;
  __VERIFIER_assert(x > 0); // INT_MAX + 1 stays positive under --ir
  return 0;
}
// Imported from ESBMC regression/ir-ra/github_10537_signed_wrap
// Needs: --ir
// RUN: --ir --z3
// MODE: FUTURE
// EXPECT: ^VERIFICATION SUCCESSFUL$
