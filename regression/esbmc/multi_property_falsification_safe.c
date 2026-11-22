/* Safe twin of multi_property_falsification. --falsification has no forward
   condition, so it proves nothing; escalating must not turn that into FAILED. */
#include <assert.h>

int main()
{
  unsigned n = nondet_uint();
  unsigned x = 0;
  __VERIFIER_assume(n < 5);
  for (unsigned i = 0; i < n; ++i)
    ++x;
  assert(x == n);
  assert(x < 5);
}
// Imported from ESBMC regression/esbmc/multi_property_falsification_safe
// Needs: --falsification
// RUN: --falsification --multi-property --max-k-step 10
// MODE: FUTURE
// EXPECT: ^\s+UNKNOWN\s+\[main\.assertion\.1\]\s+line\s+12\s+assertion x == n$
// EXPECT: ^\s+UNKNOWN\s+\[main\.assertion\.2\]\s+line\s+13\s+assertion x < 5$
// EXPECT: ^VERIFICATION UNKNOWN$
// EXPECT: \A(?![\s\S]*VERIFICATION FAILED)[\s\S]*\Z
