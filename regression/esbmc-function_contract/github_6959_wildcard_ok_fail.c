/* github #6959: "*" still accepts a function whose clauses call nothing;
 * here f breaks its ensures. */
int f(int x)
{
  __ESBMC_requires(x > 200);
  __ESBMC_ensures(__ESBMC_return_value == x + 1);
  return x + 2;
}

int main(void)
{
  int n;
  __ESBMC_assume(n > 200);
  return f(n);
}
// Imported from ESBMC regression/function_contract/github_6959_wildcard_ok_fail
// Needs: --enforce-contract *
// RUN: --enforce-contract "*" --function f
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
// EXPECT: ^  contract ensures$
