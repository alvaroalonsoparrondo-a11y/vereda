typedef struct
{
  int coeffs[4];
} P;

void f(void)
{
  P *v;
  __ESBMC_requires(__ESBMC_is_fresh(&v, sizeof(P)));
}

int main(void)
{
  return 0;
}
// Imported from ESBMC regression/function_contract/is_fresh_addr_ptr_local_pass
// Needs: --enforce-contract f
// RUN: --function f --enforce-contract f --no-pointer-check --unwind 4
// MODE: FUTURE
// EXPECT: ^VERIFICATION SUCCESSFUL$
