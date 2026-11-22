int g;
int probe(void);

int f(int x)
{
  g = probe();
  __ESBMC_requires(g > 100);
  __ESBMC_ensures(g > 100);
  return x;
}

int main(void)
{
  return f(5);
}
// Imported from ESBMC regression/function_contract/clause_call_global_ok
// Needs: --enforce-contract f
// RUN: --enforce-contract f
// MODE: FUTURE
// EXPECT: ^VERIFICATION SUCCESSFUL$
