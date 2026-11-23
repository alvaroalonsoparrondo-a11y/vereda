/* #7900 §7 question 2: x > 0 is inductive on its own, y != ... is not. */
#include <assert.h>
int __VERIFIER_nondet_int(void);
int main(void)
{
  int x = __VERIFIER_nondet_int(), y = 0;
  __VERIFIER_assume(x > 0);
  while (__VERIFIER_nondet_int())
  {
    assert(x > 0);
    assert(y != 3);
    y = 1 - y;
  }
  return 0;
}
// Imported from ESBMC regression/k-induction/multi_property_inductive_sibling_unknown
// Needs: --k-induction
// RUN: --k-induction --multi-property --max-k-step 5
// MODE: FUTURE
// EXPECT: ^\s+PASSED\s+\[main\.assertion\.1\]\s+line\s+10\s+assertion x > 0$
// EXPECT: ^\s+UNKNOWN\s+\[main\.assertion\.2\]\s+line\s+11\s+assertion y != 3 \(inductive step could not prove this claim\)$
// EXPECT: ^VERIFICATION UNKNOWN$
