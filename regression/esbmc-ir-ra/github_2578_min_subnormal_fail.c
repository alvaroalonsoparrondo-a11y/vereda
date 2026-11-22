// #2578: the smallest subnormal itself remains a possible nondet value.
#include <assert.h>

int main(void)
{
  float f;
  double d;
  if (f > 0.0f)
    assert(f >= 0x1p-148f);
  if (d < 0.0)
    assert(d <= -0x1p-1073);
  return 0;
}
// Imported from ESBMC regression/ir-ra/github_2578_min_subnormal_fail
// Needs: --ir
// RUN: --ir --z3 --multi-property
// MODE: FUTURE
// EXPECT: ^  FAILED +\[main.assertion.1\]
// EXPECT: ^  FAILED +\[main.assertion.2\]
// EXPECT: ^VERIFICATION FAILED$
