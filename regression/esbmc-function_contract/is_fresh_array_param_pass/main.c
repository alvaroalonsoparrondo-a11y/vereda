void f(int a[10])
{
  __ESBMC_requires(__ESBMC_is_fresh(a, 10 * sizeof(int)));
}

int main(void)
{
  return 0;
}
// Imported from ESBMC regression/function_contract/is_fresh_array_param_pass
// Needs: --enforce-contract f
// RUN: --function f --enforce-contract f --no-pointer-check --unwind 4
// MODE: FUTURE
// EXPECT: ^VERIFICATION SUCCESSFUL$
