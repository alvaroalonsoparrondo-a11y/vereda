/* #9000: a user assertion that shares a macro expansion, and so a location,
 * with a clause survives when the clauses of an inactive function are
 * dropped. */
#include <assert.h>
#define SPEC(x)                                                                \
  assert((x) > 5);                                                             \
  __ESBMC_requires((x) > 0)
int g(int x)
{
  SPEC(x);
  return x;
}
int f(int a)
{
  __ESBMC_requires(a > 0);
  __ESBMC_ensures(__ESBMC_return_value > 0);
  return a;
}
int main()
{
  int v = 1;
  g(v);
  return 0;
}
// Imported from ESBMC regression/function_contract/github_9000_macro_assert_before_clause_fail
// Needs: --enforce-contract f
// RUN: --enforce-contract f
// MODE: FUTURE
// EXPECT: ^  assertion \(x\) > 5$
// EXPECT: ^VERIFICATION FAILED$
