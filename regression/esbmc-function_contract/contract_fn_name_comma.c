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
// Imported from ESBMC regression/function_contract/contract_fn_name_comma
// Needs: --replace-call-with-contract f,g
// RUN: --replace-call-with-contract f,g
// MODE: FUTURE
// EXPECT: ^ERROR: --replace-call-with-contract: cannot use 'f,g': no function of that name has a body here \(names are not comma-separated; repeat the flag once per function, or use "\*"\)$
// EXPECT: \A(?!(.|\n)*VERIFICATION)
