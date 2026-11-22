/* #7900 §7 question 2: x > 0 is inductive on its own, y != ... is not. */
#include <assert.h>
int nondet_int(void);
int main(void)
{
  int x = nondet_int(), y = 0;
  __VERIFIER_assume(x > 0);
  while (nondet_int())
  {
    assert(x > 0);
    assert(y != 1);
    y = 1 - y;
  }
  return 0;
}
// Imported from ESBMC regression/k-induction/multi_property_inductive_sibling_failed
// Needs: --k-induction
// RUN: --k-induction --multi-property --max-k-step 5
// MODE: FUTURE
// EXPECT: ^\s+PASSED\s+\[main\.assertion\.1\]\s+line\s+10\s+assertion x > 0$
// EXPECT: ^\s+FAILED\s+\[main\.assertion\.2\]\s+line\s+11\s+assertion y != 1$
// EXPECT: ^\*\* 1 of 2 properties failed, 1 passed$
// EXPECT: ^VERIFICATION FAILED$
