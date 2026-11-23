#include <assert.h>
int main(void)
{
  int x = 0;
  if (x)
    assert(0);
  assert(x == 0);
  return 0;
}
// Imported from ESBMC regression/esbmc/report_unreached_claims_off
// EXPECT: ^VERIFICATION SUCCESSFUL$
// EXPECT: ^\*\* 0 of 1 properties failed, 1 passed$
// EXPECT: (?s)\A(?!.*never reached)
// Vereda: unmet EXPECT: ^\*\* 0 of 1 properties failed, 1 passed$
// MODE: FUTURE
