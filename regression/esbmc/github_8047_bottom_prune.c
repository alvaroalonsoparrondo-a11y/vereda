// #8047: the else-branch assume empties the domain; the merge must replace
// that bottom with the other path's domain, so the claim is still discharged.
int main()
{
  int x;
  __ESBMC_assume(x >= 0 && x <= 10);
  if (x == 5)
    ;
  else
    __ESBMC_assume(x == 20);
  __ESBMC_assert(x <= 10, "x at most 10");
}
// Imported from ESBMC regression/esbmc/github_8047_bottom_prune
// Needs: --interval-symex-assert
// RUN: --interval-symex-assert
// MODE: FUTURE
// EXPECT: ^ +PASSED .*line 11 +x at most 10 \(interval\)$
// EXPECT: ^VERIFICATION SUCCESSFUL$
