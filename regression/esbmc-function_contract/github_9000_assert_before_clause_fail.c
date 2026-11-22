/* #9000: dropping the clauses of a function that is neither replaced nor
 * enforced keeps a body assertion that directly precedes one of them. */
int g;
void f(int x)
{
  __ESBMC_ensures(g == x);
  __ESBMC_assigns(g);
  g = x;
}
int half(int c)
{
  __VERIFIER_assert(c > 0); // half needs a positive argument
  __ESBMC_ensures(__ESBMC_return_value == c / 2);
  return c / 2;
}
int main()
{
  f(0);
  half(g);
  return 0;
}
// Imported from ESBMC regression/function_contract/github_9000_assert_before_clause_fail
// Needs: --replace-call-with-contract f
// RUN: --replace-call-with-contract f
// MODE: FUTURE
// EXPECT: ^  half needs a positive argument$
// EXPECT: ^VERIFICATION FAILED$
