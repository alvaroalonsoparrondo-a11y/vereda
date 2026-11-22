/* github #6959: "*" still accepts a function whose clauses call nothing. */
int f(int x)
{
  __ESBMC_requires(x > 200);
  __ESBMC_ensures(__ESBMC_return_value == x + 1);
  return x + 1;
}

int main(void)
{
  int n;
  __VERIFIER_assume(n > 200);
  return f(n);
}
// Imported from ESBMC regression/function_contract/github_6959_wildcard_ok
// Needs: --enforce-contract *
// RUN: --enforce-contract "*" --function f
// MODE: FUTURE
// EXPECT: ^VERIFICATION SUCCESSFUL$
