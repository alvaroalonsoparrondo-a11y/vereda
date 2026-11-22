int helper(int x) { return x + 1; }

int f(int x)
{
  __ESBMC_requires(helper(x) > 100);
  __ESBMC_ensures(__ESBMC_return_value > 100);
  return x + 1;
}

int main(void)
{
  int r = f(500);
  __VERIFIER_assert(r > 100); // contract promises this
  return 0;
}
// Imported from ESBMC regression/function_contract/clause_call_replace
// Needs: --replace-call-with-contract f
// RUN: --replace-call-with-contract f
// MODE: FUTURE
// EXPECT: ^ERROR: --replace-call-with-contract: cannot use 'f': a contract clause calls 'c:@F@helper', whose result the clause cannot name outside the function body$
