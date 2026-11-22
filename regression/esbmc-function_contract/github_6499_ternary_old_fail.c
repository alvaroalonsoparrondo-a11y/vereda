int g;

void f(int c)
{
  __ESBMC_requires(c == 1);
  __ESBMC_assigns(g);
  /* c is 1, so the then-arm applies. It is FALSE: g becomes 0, not 99.
     The else-arm is a tautology. A correct reconstruction must FAIL. */
  __ESBMC_ensures(
    c ? (g == 99 && __ESBMC_old(g) == __ESBMC_old(g))
      : (__ESBMC_old(g) == __ESBMC_old(g)));
  g = 0;
}

int main(void) { return 0; }
// Imported from ESBMC regression/function_contract/github_6499_ternary_old_fail
// Needs: --enforce-contract f
// RUN: --function f --enforce-contract f
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
