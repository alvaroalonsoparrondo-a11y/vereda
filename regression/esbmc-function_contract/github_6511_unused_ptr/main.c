// The contract states no extent for `out`, but nothing here reads or writes
// through it, so the unstated-extent advice does not apply (#6511).
void f(int *out, int v)
{
  __ESBMC_requires(v > 0);
  __ESBMC_ensures(1);
  (void)out;
}

int main(void)
{
  return 0;
}
// Imported from ESBMC regression/function_contract/github_6511_unused_ptr
// Needs: --enforce-contract f
// RUN: --enforce-contract f --function f
// MODE: FUTURE
// EXPECT: ^VERIFICATION SUCCESSFUL$
// EXPECT: (?s)\A(?!.*contract states no extent)
