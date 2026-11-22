int g;

/* An empty frame condition is the whole contract: pure writes nothing
   outside its own locals (GitHub #6555). */
int pure(int x)
{
  __ESBMC_assigns();
  return x + 1;
}

int main(void)
{
  g = 7;
  __ESBMC_assert(pure(1) == 2, "pure returns x + 1");
  __ESBMC_assert(g == 7, "pure leaves g alone");
  return 0;
}
// Imported from ESBMC regression/function_contract/assigns_empty_only
// Needs: --enforce-contract pure
// RUN: --enforce-contract pure
// MODE: FUTURE
// EXPECT: ^VERIFICATION SUCCESSFUL$
