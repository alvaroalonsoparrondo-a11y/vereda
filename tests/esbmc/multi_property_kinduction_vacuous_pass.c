#include <assert.h>
int main()
{
  unsigned n = __VERIFIER_nondet_uint();
  unsigned x = 0;
  __VERIFIER_assume(n < 5);
  for (unsigned i = 0; i < n; ++i)
    ++x;
  assert(x == n);
  return 0;
}
// Imported from ESBMC regression/esbmc/multi_property_kinduction_vacuous_pass
// Needs: --k-induction --check-vacuity
// RUN: --k-induction --multi-property --check-vacuity --max-k-step 8
// MODE: FUTURE
// EXPECT: ^VERIFICATION SUCCESSFUL$
// EXPECT: ^\s+PASSED\s+\[main\.assertion\.1\]\s+line\s+9\s+assertion x == n$
// EXPECT: ^\*\* 0 of 1 properties failed, 1 passed$
