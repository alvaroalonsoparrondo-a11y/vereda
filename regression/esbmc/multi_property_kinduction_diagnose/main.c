/* The same program without --multi-fail-fast: the base case at k = 2 solves
   every claim, so the diagnostic inductive step at max-k proves the other
   two. */
#include <assert.h>
_Bool nondet_bool();
unsigned nondet_uint();
int main()
{
  unsigned n = nondet_uint();
  __ESBMC_assume(n < 10);
  unsigned i = 0, j = 3;
  while (nondet_bool())
  {
    i++;
    assert(i != 2);
    assert(n < 10);
    assert(j == 3);
  }
  return 0;
}
// Imported from ESBMC regression/esbmc/multi_property_kinduction_diagnose
// Needs: --k-induction
// RUN: --k-induction --multi-property --max-k-step 2
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
// EXPECT: ^\s+FAILED\s+\[main\.assertion\.1\]\s+line\s+15\s+assertion i != 2$
// EXPECT: ^\s+PASSED\s+\[main\.assertion\.2\]\s+line\s+16\s+assertion n < 10$
// EXPECT: ^\s+PASSED\s+\[main\.assertion\.3\]\s+line\s+17\s+assertion j == 3$
// EXPECT: \A(?![\s\S]*This report is partial)[\s\S]*\Z
