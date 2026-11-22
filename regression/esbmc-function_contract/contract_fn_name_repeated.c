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
  __ESBMC_assert(b == 3, "true of g's body, not of g's contract");
  return a - a;
}
// Imported from ESBMC regression/function_contract/contract_fn_name_repeated
// Needs: --replace-call-with-contract f --replace-call-with-contract g
// RUN: --replace-call-with-contract f --replace-call-with-contract g
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
// EXPECT: ^Replacing calls with contracts for 2 function\(s\)$
