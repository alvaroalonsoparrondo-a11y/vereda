int plain(int x)
{
  return x + 1;
}

int f(int x)
{
  __ESBMC_ensures(__ESBMC_return_value >= 0);
  return x > 0 ? x : 0;
}

int main(void)
{
  return f(3) - plain(2);
}
// Imported from ESBMC regression/function_contract/contract_fn_name_no_contract
// Needs: --replace-call-with-contract plain
// RUN: --replace-call-with-contract plain
// MODE: FUTURE
// EXPECT: ^ERROR: --replace-call-with-contract: cannot use 'plain': that function declares no contract clauses$
// EXPECT: \A(?!(.|\n)*VERIFICATION)
