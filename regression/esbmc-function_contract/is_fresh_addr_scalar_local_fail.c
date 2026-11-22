void f(void)
{
  int x;
  __ESBMC_requires(__ESBMC_is_fresh(&x, sizeof(int)));
}

int main(void)
{
  return 0;
}
// Imported from ESBMC regression/function_contract/is_fresh_addr_scalar_local_fail
// Needs: --enforce-contract f
// RUN: --function f --enforce-contract f --no-pointer-check --unwind 4
// MODE: FUTURE
// EXPECT: ^ERROR: __ESBMC_is_fresh needs a pointer it can point at fresh storage
