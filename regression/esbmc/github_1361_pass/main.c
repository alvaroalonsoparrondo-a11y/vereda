/* Safe twin of github_1361: one table, two passing rows, and the base cases
   report no verdict of their own. */
#include <assert.h>

int main()
{
  for (int i = 0; i < 2; i++)
  {
    assert(i < 5);
  }
  assert(1 != 2);
  return 0;
}
// Imported from ESBMC regression/esbmc/github_1361_pass
// Needs: --k-induction
// RUN: --k-induction --multi-property
// MODE: FUTURE
// EXPECT: ^VERIFICATION SUCCESSFUL$
// EXPECT: ^No bug has been found in the base case$
// EXPECT: ^\s+PASSED\s+\[main\.assertion\.1\]\s+line\s+9\s+assertion i < 5$
// EXPECT: ^\s+PASSED\s+\[main\.assertion\.2\]\s+line\s+11\s+assertion 1 != 2$
// EXPECT: ^\*\* 0 of 2 properties failed, 2 passed$
