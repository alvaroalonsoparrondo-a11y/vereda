int plain(int x)
{
  return x + 1;
}

int main(void)
{
  return plain(2) - 3;
}
// Imported from ESBMC regression/function_contract/contract_fn_name_star_no_contract
// Needs: --replace-call-with-contract *
// RUN: --replace-call-with-contract "*"
// MODE: FUTURE
// EXPECT: ^ERROR: --replace-call-with-contract: no function with a contract to act on$
// EXPECT: \A(?!(.|\n)*VERIFICATION)
