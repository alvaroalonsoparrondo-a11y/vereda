/* The base case at k = 2 finds the first claim violated in the second
   iteration, and --multi-fail-fast skips the other claims' instances there.
   The diagnostic inductive step at max-k proves both inductive -- the third
   by the simplifier alone -- but that round did not back either proof. */
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
// Imported from ESBMC regression/esbmc/multi_property_kinduction_diagnose_fail_fast
// Needs: --k-induction --multi-fail-fast 1
// RUN: --k-induction --multi-property --multi-fail-fast 1 --max-k-step 2
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
// EXPECT: ^\s+FAILED\s+\[main\.assertion\.1\]\s+line\s+16\s+assertion i != 2$
// EXPECT: ^\s+UNKNOWN\s+\[main\.assertion\.2\]\s+line\s+17\s+assertion n < 10
// EXPECT: ^\s+UNKNOWN\s+\[main\.assertion\.3\]\s+line\s+18\s+assertion j == 3
// EXPECT: ^This report is partial: the run stopped before every property reached a verdict
