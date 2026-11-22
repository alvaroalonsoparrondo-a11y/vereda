#include <assert.h>
int main(void)
{
  int x = 0;
  if (x)
    assert(0);
  assert(x == 0);
  return 0;
}
// Imported from ESBMC regression/esbmc/report_unreached_claims
// Needs: --report-unreached-claims
// RUN: --report-unreached-claims
// MODE: FUTURE
// EXPECT: ^VERIFICATION SUCCESSFUL$
// EXPECT: ^\s+PASSED\s+\[main\.assertion\.1\]\s+line\s+6\s+assertion 0 \(never reached\)$
// EXPECT: ^\*\* 0 of 2 properties failed, 2 passed \(1 never reached\)$
