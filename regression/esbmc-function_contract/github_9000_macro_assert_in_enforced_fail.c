/* #9000: a user assertion that shares a macro expansion with a clause of an
 * enforced function stays in the function's body. */
#include <assert.h>
#define SPEC(x)                                                                \
  assert((x) > 5);                                                             \
  __ESBMC_requires((x) > 0)
int f(int a)
{
  SPEC(a);
  __ESBMC_ensures(__ESBMC_return_value > 0);
  return a;
}
int main()
{
  return 0;
}
// Imported from ESBMC regression/function_contract/github_9000_macro_assert_in_enforced_fail
// Needs: --enforce-contract f
// RUN: --function f --enforce-contract f
// MODE: FUTURE
// EXPECT: ^  assertion \(a\) > 5$
// EXPECT: ^VERIFICATION FAILED$
