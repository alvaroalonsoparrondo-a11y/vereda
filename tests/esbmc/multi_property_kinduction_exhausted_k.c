/* Neither the forward condition nor the inductive step can settle this loop,
   so the k steps run out and the driver reports the table itself. */
#include <assert.h>

int main()
{
  int x = 0;
  while (1)
  {
    assert(x < 3);
    assert(x != 100);
    ++x;
  }
}
// Imported from ESBMC regression/esbmc/multi_property_kinduction_exhausted_k
// Needs: --k-induction
// RUN: --k-induction --multi-property --max-k-step 5
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
// EXPECT: ^\s+FAILED\s+\[main\.assertion\.1\]\s+line\s+10\s+assertion x < 3$
// EXPECT: ^\s+UNKNOWN\s+\[main\.assertion\.2\]\s+line\s+11\s+assertion x != 100 \(inductive step could not prove this claim\)$
// EXPECT: ^\*\* 1 of 2 properties failed, 1 unknown$
// EXPECT: \A(?![\s\S]*VERIFICATION SUCCESSFUL)[\s\S]*\Z
