int g;

/* Declares an empty frame condition but writes a global: the assigns
   compliance check must catch it (GitHub #6555). */
int impure(int x)
{
  __ESBMC_assigns();
  g = x;
  return x + 1;
}

int main(void)
{
  return impure(1) - 2;
}
// Imported from ESBMC regression/function_contract/assigns_empty_only_fail
// Needs: --enforce-contract impure
// RUN: --enforce-contract impure
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
// EXPECT: assigns compliance: c:@g not in assigns clause
