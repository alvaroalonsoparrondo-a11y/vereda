/* The second claim is violated only at k = 4, so --falsification must keep
   escalating past the first violation to report it (esbmc/esbmc#7900). */
#include <assert.h>

int main()
{
  unsigned n = nondet_uint();
  unsigned x = 0;
  assert(n != 7);
  for (unsigned i = 0; i < n; ++i)
    ++x;
  assert(x != 3);
}
// Imported from ESBMC regression/esbmc/multi_property_falsification
// Needs: --falsification
// RUN: --falsification --multi-property --max-k-step 10
// MODE: FUTURE
// EXPECT: ^\s+FAILED\s+\[main\.assertion\.1\]\s+line\s+9\s+assertion n != 7$
// EXPECT: ^\s+FAILED\s+\[main\.assertion\.2\]\s+line\s+12\s+assertion x != 3$
// EXPECT: ^\*\* 2 of 2 properties failed$
// EXPECT: ^VERIFICATION FAILED$
