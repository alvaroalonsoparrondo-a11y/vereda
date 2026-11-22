/* github #6959: "*" selects f, so its clause call is reported as it is when
 * f is named. */
int helper(int x) { return x + 1; }

int f(int x)
{
  __ESBMC_requires(x > 200);
  __ESBMC_ensures(__ESBMC_return_value == helper(x));
  return x + 1;
}

int main(void)
{
  int n;
  __ESBMC_assume(n > 200);
  return f(n);
}
// Imported from ESBMC regression/function_contract/github_6959_enforce_wildcard
// Needs: --enforce-contract *
// RUN: --enforce-contract "*" --function f
// MODE: FUTURE
// EXPECT: ^ERROR: --enforce-contract: cannot use 'c:@F@f': a contract clause calls 'c:@F@helper', whose result the clause cannot name outside the function body$
