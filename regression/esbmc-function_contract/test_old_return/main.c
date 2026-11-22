// Test __ESBMC_old() with function return value

int counter = 0;

int increment_and_return(int delta)
{
  __ESBMC_requires(delta > 0);
  __ESBMC_ensures(counter == __ESBMC_old(counter) + delta);
  __ESBMC_ensures(__ESBMC_return_value == __ESBMC_old(counter) + delta);

  counter += delta;
  return counter;
}

int main()
{
  counter = 10;
  int result = increment_and_return(5);
  assert(result == 15);
  assert(counter == 15);
  return 0;
}
// Imported from ESBMC regression/function_contract/test_old_return
// Needs: --enforce-contract *
// RUN: --enforce-contract "*"
// MODE: FUTURE
// EXPECT: ^VERIFICATION SUCCESSFUL$
