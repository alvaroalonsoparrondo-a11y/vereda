// Test __ESBMC_old() with negative values and subtraction

int balance = 0;

void withdraw(int amount)
{
  __ESBMC_requires(amount > 0);
  __ESBMC_requires(__ESBMC_old(balance) >= amount);
  __ESBMC_ensures(balance == __ESBMC_old(balance) - amount);

  balance -= amount;
}

int main()
{
  balance = 100;
  withdraw(30);
  assert(balance == 70);
  return 0;
}
// Imported from ESBMC regression/function_contract/test_old_negative
// Needs: --enforce-contract *
// RUN: --enforce-contract "*"
// MODE: FUTURE
// EXPECT: ^VERIFICATION SUCCESSFUL$
