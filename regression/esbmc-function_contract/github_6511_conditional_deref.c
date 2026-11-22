// `out` is dereferenced on one path only. Suppressing the unstated-extent
// advice here would be wrong: this is exactly the contract whose bounds check
// fails once v > 100 is reachable (#6511).
void f(int *out, int v)
{
  __ESBMC_requires(v > 0);
  __ESBMC_ensures(1);
  if (v > 100)
    *out = v;
}

int main(void)
{
  return 0;
}
// Imported from ESBMC regression/function_contract/github_6511_conditional_deref
// Needs: --enforce-contract f
// RUN: --enforce-contract f --function f
// MODE: FUTURE
// EXPECT: contract states no extent for pointer parameter\(s\) out
