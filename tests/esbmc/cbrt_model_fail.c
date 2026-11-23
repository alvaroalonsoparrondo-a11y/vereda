#include <assert.h>
#include <math.h>

int main()
{
  double r = cbrt(2.0);
  assert(r > 1.2599 && r < 1.26);
  assert(r == 1.25);
  return 0;
}
// Imported from ESBMC regression/esbmc/cbrt_model_fail
// RUN: --multi-property
// EXPECT: ^VERIFICATION FAILED$
// EXPECT: ^\*\* 1 of 2 properties failed, 1 passed$
// EXPECT: FAILED\s+\[main.assertion.2\].*r == 1.25
// Vereda: unmet EXPECT: ^\*\* 1 of 2 properties failed, 1 passed$
// MODE: FUTURE
