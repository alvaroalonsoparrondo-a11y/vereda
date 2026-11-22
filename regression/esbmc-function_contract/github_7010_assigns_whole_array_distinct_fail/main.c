// The whole-array havoc has to leave the elements independent. ARRAY_OF(NONDET)
// ties them to one value, so an ensures naming two different values had no
// post-state to land in and the path died before reaching the assert.
#include <assert.h>

int a[4];

void f(void)
{
  __ESBMC_assigns(a);
  __ESBMC_ensures(a[0] == 1 && a[1] == 2);
  a[0] = 1;
  a[1] = 2;
}

int main(void)
{
  f();
  assert(a[0] == 1 && a[1] == 2); /* holds under the contract */
  assert(0);                      /* reachable */
  return 0;
}
// Imported from ESBMC regression/function_contract/github_7010_assigns_whole_array_distinct_fail
// Needs: --replace-call-with-contract *
// RUN: --replace-call-with-contract "*" --unwind 8
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
