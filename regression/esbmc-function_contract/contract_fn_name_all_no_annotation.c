int f(int x)
{
  __ESBMC_ensures(__ESBMC_return_value > x);
  return x + 1;
}

int main(void)
{
  return f(1) - 2;
}
// Imported from ESBMC regression/function_contract/contract_fn_name_all_no_annotation
// Needs: --enforce-all-contracts
// RUN: --enforce-all-contracts
// MODE: FUTURE
// EXPECT: ^ERROR: --enforce-all-contracts: no function carries the __ESBMC_contract annotation$
// EXPECT: \A(?!(.|\n)*VERIFICATION)
