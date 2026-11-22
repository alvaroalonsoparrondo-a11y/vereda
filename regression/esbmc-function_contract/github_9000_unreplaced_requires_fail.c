/* #9000: a requires in a function that is neither replaced nor enforced
 * must not be assumed at its call sites. */
int g;
void f(int x)
{
  __ESBMC_ensures(g == x);
  __ESBMC_assigns(g);
  g = x;
}
int half(int c)
{
  __ESBMC_requires(c > 0);
  __ESBMC_ensures(1);
  __VERIFIER_assert(c > 0); // half needs a positive argument
  return c / 2;
}
int main()
{
  f(0);
  half(g);
  return 0;
}
// Imported from ESBMC regression/function_contract/github_9000_unreplaced_requires_fail
// Needs: --replace-call-with-contract f
// RUN: --replace-call-with-contract f
// MODE: FUTURE
// EXPECT: ^  half needs a positive argument$
// EXPECT: ^VERIFICATION FAILED$
