/* extern_fn is declared, has no body here, and IS called: the flag must be
   rejected because the body is absent, not because nothing calls it. */
int extern_fn(int x);

int f(int x)
{
  __ESBMC_ensures(__ESBMC_return_value >= 0);
  return x > 0 ? x : 0;
}

int main(void)
{
  return f(3) + extern_fn(1) - 3;
}
// Imported from ESBMC regression/function_contract/contract_fn_name_no_body
// Needs: --replace-call-with-contract extern_fn
// RUN: --replace-call-with-contract extern_fn
// MODE: FUTURE
// EXPECT: ^ERROR: --replace-call-with-contract: cannot use 'extern_fn': no function of that name has a body here$
// EXPECT: \A(?!(.|\n)*VERIFICATION)
