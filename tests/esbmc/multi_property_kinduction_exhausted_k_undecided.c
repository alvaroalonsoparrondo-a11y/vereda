/* The same loop with nothing violated within the bound: the run ends UNKNOWN
   and every row says so, rather than the base cases reporting proofs. */
#include <assert.h>

int main()
{
  int x = 0;
  while (1)
  {
    assert(x != 100);
    ++x;
  }
}
// Imported from ESBMC regression/esbmc/multi_property_kinduction_exhausted_k_undecided
// Needs: --k-induction
// RUN: --k-induction --multi-property --max-k-step 5
// MODE: FUTURE
// EXPECT: ^Unable to prove or falsify the program, giving up\.$
// EXPECT: ^VERIFICATION UNKNOWN$
// EXPECT: ^\s+UNKNOWN\s+\[main\.assertion\.1\]\s+line\s+10\s+assertion x != 100 \(inductive step could not prove this claim\)$
// EXPECT: ^\*\* 0 of 1 properties failed, 1 unknown$
// EXPECT: \A(?![\s\S]*VERIFICATION SUCCESSFUL)[\s\S]*\Z
