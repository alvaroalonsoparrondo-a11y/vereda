// #2578: with g == 0, h == f, so h > f fails.
#include <assert.h>
#include <math.h>
#include <fenv.h>

int main(void)
{
  float f;
  float g;

  __VERIFIER_assume(!isnan(f));
  __VERIFIER_assume(!isnan(g));

  if (f > g)
    fesetround(FE_UPWARD);

  if (f < g)
    fesetround(FE_DOWNWARD);

  if (!isinf(f) && g >= 0.0f)
  {
    float h = f + g;
    assert(h > f);
  }

  return 0;
}
// Imported from ESBMC regression/ir-ra/github_2578_fail
// Needs: --ir
// RUN: --ir --z3
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
