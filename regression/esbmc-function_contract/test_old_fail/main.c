// Test __ESBMC_old() - this should FAIL verification

int global = 0;

void increment_global_wrong(int x)
{
  __ESBMC_requires(x > 0);
  __ESBMC_ensures(global == __ESBMC_old(global) + x);

  // BUG: incrementing by x+1 instead of x
  global += (x + 1);
}

int main()
{
  global = 10;
  increment_global_wrong(5);
  return 0;
}
// Imported from ESBMC regression/function_contract/test_old_fail
// Needs: --enforce-contract *
// RUN: --enforce-contract "*"
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
