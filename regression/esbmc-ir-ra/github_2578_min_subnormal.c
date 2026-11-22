// #2578: a nondet float is no closer to zero than the smallest subnormal.
#include <assert.h>

int main(void)
{
  float f;
  double d;
  if (f > 0.0f)
    assert(f >= 0x1p-149f);
  if (d < 0.0)
    assert(d <= -0x1p-1074);
  return 0;
}
// Imported from ESBMC regression/ir-ra/github_2578_min_subnormal
// Needs: --ir
// RUN: --ir --z3
// MODE: FUTURE
// EXPECT: ^VERIFICATION SUCCESSFUL$
