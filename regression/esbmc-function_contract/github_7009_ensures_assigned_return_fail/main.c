#include <assert.h>

int f(void)
{
  __ESBMC_ensures(__ESBMC_return_value == 1);
  return 1;
}

int main(void)
{
  int r = 200;
  r = f();
  assert(0);
  return 0;
}
// Imported from ESBMC regression/function_contract/github_7009_ensures_assigned_return_fail
// Needs: --replace-call-with-contract *
// RUN: --replace-call-with-contract "*"
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
