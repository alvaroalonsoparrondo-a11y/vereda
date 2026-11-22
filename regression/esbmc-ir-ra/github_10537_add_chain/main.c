int nondet_int(void);
int main()
{
  /* 2000000000 + 2000000000 does not fit an int, so the chain keeps both. */
  int x = nondet_int();
  __ESBMC_assume(x >= 0 && x <= 10);
  int y = (x + 2000000000) + 2000000000;
  __ESBMC_assert(y > 0, "the constants are folded only if they fit");
  return 0;
}
// Imported from ESBMC regression/ir-ra/github_10537_add_chain
// Needs: --ir
// RUN: --ir --z3
// MODE: FUTURE
// EXPECT: ^VERIFICATION SUCCESSFUL$
