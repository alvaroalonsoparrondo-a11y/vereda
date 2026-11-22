int helper(int x) { return x + 1; }

int f(int x)
{
  __ESBMC_requires(helper(x) > 100);
  __ESBMC_ensures(__ESBMC_return_value > 100);
  return x + 1;
}

int main(void)
{
  int n;
  __VERIFIER_assume(n > 200);
  return f(n);
}
// Imported from ESBMC regression/function_contract/clause_call_requires
// Needs: --enforce-contract f
// RUN: --enforce-contract f --function f
// MODE: FUTURE
// EXPECT: ^ERROR: --enforce-contract: cannot use 'f': a contract clause calls 'c:@F@helper', whose result the clause cannot name outside the function body$
