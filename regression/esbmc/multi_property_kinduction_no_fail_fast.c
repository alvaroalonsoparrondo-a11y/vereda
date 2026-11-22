/* The same program without --multi-fail-fast: every claim is solved at every
   base case, so the forward condition's proof reaches the second one even
   though the first was violated at k = 1. */
#include <assert.h>

int main()
{
  unsigned n = nondet_uint();
  unsigned m = nondet_uint();
  assert(n != 7);
  assert(m + 1 > m || m == 0xffffffffu);
  return 0;
}
// Imported from ESBMC regression/esbmc/multi_property_kinduction_no_fail_fast
// Needs: --k-induction
// RUN: --k-induction --multi-property --max-k-step 3
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
// EXPECT: ^\s+FAILED\s+\[main\.assertion\.1\]\s+line\s+10\s+assertion n != 7$
// EXPECT: ^\s+PASSED\s+\[main\.assertion\.2\]\s+line\s+11\s+assertion m \+ 1 > m
// EXPECT: \A(?![\s\S]*This report is partial)[\s\S]*\Z
