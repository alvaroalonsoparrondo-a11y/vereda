/* github.com/esbmc/esbmc/issues/1361: both assertions must reach the report,
   in one table, with an id each. */
#include <assert.h>

int main()
{
  for (int i = 0; i < 2; i++)
  {
    assert(2 == 3);
  }
  assert(1 == 2);
  return 0;
}
// Imported from ESBMC regression/esbmc/github_1361
// Needs: --k-induction
// RUN: --k-induction --multi-property
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
// EXPECT: ^\s+FAILED\s+\[main\.assertion\.1\]\s+line\s+9\s+assertion 2 == 3$
// EXPECT: ^\s+FAILED\s+\[main\.assertion\.2\]\s+line\s+11\s+assertion 1 == 2$
// EXPECT: ^\*\* 2 of 2 properties failed$
// EXPECT: \A(?![\s\S]*VERIFICATION SUCCESSFUL)[\s\S]*\Z
