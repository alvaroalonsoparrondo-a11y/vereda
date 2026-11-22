#include <assert.h>

int f(void)
{
  __ESBMC_ensures(__ESBMC_return_value == 1);
  return 1;
}

int main(void)
{
  int r = f();
  assert(r == 1);
  return 0;
}
// Imported from ESBMC regression/function_contract/github_7009_ensures_init_return
// Needs: --replace-call-with-contract *
// RUN: --replace-call-with-contract "*"
// MODE: FUTURE
// EXPECT: ^VERIFICATION SUCCESSFUL$
