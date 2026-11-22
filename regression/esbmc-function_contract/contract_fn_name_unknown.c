int f(int x)
{
  __ESBMC_ensures(__ESBMC_return_value >= 0);
  return x > 0 ? x : 0;
}

int g(int x)
{
  __ESBMC_ensures(__ESBMC_return_value >= 0);
  return x > 0 ? x : 0;
}

int main(void)
{
  int a = f(3);
  int b = g(3);
  __VERIFIER_assert(b == 3); // true of g's body, not of g's contract
  return a - a;
}
// Imported from ESBMC regression/function_contract/contract_fn_name_unknown
// Needs: --replace-call-with-contract no_such_function
// RUN: --replace-call-with-contract no_such_function
// MODE: FUTURE
// EXPECT: ^ERROR: --replace-call-with-contract: cannot use 'no_such_function': no function of that name has a body here$
// EXPECT: \A(?!(.|\n)*VERIFICATION)
