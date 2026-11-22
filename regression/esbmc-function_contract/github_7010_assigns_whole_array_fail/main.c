// `__ESBMC_assigns(a)` reached the havoc as `a[0]`, because `&a` is `&a[0]` by
// then and an element the source named looks exactly the same. Every other
// element kept its pre-call value, so the ensures below was `assume false` and
// the reachable assert(0) went unreported.
#include <assert.h>

int a[4];

void f(void)
{
  __ESBMC_assigns(a);
  __ESBMC_ensures(a[0] == 1 && a[1] == 1 && a[2] == 1 && a[3] == 1);
  for (int i = 0; i < 4; i++)
    a[i] = 1;
}

int main(void)
{
  f();
  assert(a[3] == 1); /* holds under the contract */
  assert(0);         /* reachable, so the only correct answer is FAILED */
  return 0;
}
// Imported from ESBMC regression/function_contract/github_7010_assigns_whole_array_fail
// Needs: --replace-call-with-contract *
// RUN: --replace-call-with-contract "*" --unwind 8
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
