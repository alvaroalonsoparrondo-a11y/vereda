/* #9000: the clauses of a function that is neither replaced nor enforced are
 * not evaluated, so its ensures cannot raise a division by zero. */
int g;
void f(int x)
{
  __ESBMC_ensures(g == x);
  __ESBMC_assigns(g);
  g = x;
}
int ratio(int c)
{
  __ESBMC_ensures(__ESBMC_return_value == 100 / c);
  return c == 0 ? 0 : 100 / c;
}
int main()
{
  f(0);
  int r = ratio(g);
  __VERIFIER_assert(r == 0 && g == 0); // ratio(0) is 0
  return 0;
}
// Imported from ESBMC regression/function_contract/github_9000_unreplaced_clause_unevaluated
// Needs: --replace-call-with-contract f
// RUN: --replace-call-with-contract f
// MODE: FUTURE
// EXPECT: ^VERIFICATION SUCCESSFUL$
