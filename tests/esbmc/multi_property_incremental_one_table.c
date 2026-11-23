/* Two claims violated at different k. Both belong in one table, and the
   forward condition's unwinding assertion is not a property of the program. */
#include <assert.h>

int main()
{
  unsigned n = __VERIFIER_nondet_uint();
  unsigned x = 0;
  assert(n != 7);
  for (unsigned i = 0; i < n; ++i)
    ++x;
  assert(x != 3);
}
// Imported from ESBMC regression/esbmc/multi_property_incremental_one_table
// RUN: --incremental-bmc --multi-property --max-k-step 10
// EXPECT: ^VERIFICATION FAILED$
// EXPECT: ^\s+FAILED\s+\[main\.assertion\.1\]\s+line\s+9\s+assertion n != 7$
// EXPECT: ^\s+FAILED\s+\[main\.assertion\.2\]\s+line\s+12\s+assertion x != 3$
// EXPECT: ^\*\* 2 of 2 properties failed$
// EXPECT: \A(?![\s\S]*VERIFICATION SUCCESSFUL)[\s\S]*\Z
// Vereda: unmet EXPECT: ^\s+FAILED\s+\[main\.assertion\.1\]\s+line\s+9\s+assertion n != 7$
// MODE: FUTURE
