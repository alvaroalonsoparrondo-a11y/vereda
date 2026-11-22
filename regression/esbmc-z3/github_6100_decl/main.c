int helper(int a)
{
  int t = a * 2;
  return t + 1;
}

int main()
{
  int x;
  __ESBMC_assert(
    __ESBMC_forall(&x, helper(x) - 2 * x == 1), "decl body inlines");
}
// Imported from ESBMC regression/z3/github_6100_decl
// RUN: --solver z3
// MODE: THOROUGH
// EXPECT: ^VERIFICATION SUCCESSFUL$
