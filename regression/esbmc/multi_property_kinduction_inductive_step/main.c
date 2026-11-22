#include <assert.h>
int main()
{
  unsigned n = nondet_uint();
  unsigned i = 0;
  while (i < n)
  {
    ++i;
    assert(i <= n);
  }
  return 0;
}
// Imported from ESBMC regression/esbmc/multi_property_kinduction_inductive_step
// Needs: --k-induction
// RUN: --k-induction --multi-property --max-k-step 8
// MODE: FUTURE
// EXPECT: ^Solution found by the inductive step \(k = 2\)$
// EXPECT: ^VERIFICATION SUCCESSFUL$
// EXPECT: ^\s+PASSED\s+\[main\.assertion\.1\]\s+line\s+9\s+assertion i <= n$
// EXPECT: ^\*\* 0 of 1 properties failed, 1 passed$
// EXPECT: ^No bug has been found in the base case$
