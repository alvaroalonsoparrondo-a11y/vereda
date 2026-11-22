#include <assert.h>

int main()
{
  int x = 0;
  for (int i = 0; i < 3; i++)
  {
    x++;
    __ESBMC_ltl_sample();
  }
  assert(x == 3);
  return 0;
}
// Imported from ESBMC regression/ltl/sample-points-no-ltl
// RUN: --unwind 4
// EXPECT: ^VERIFICATION SUCCESSFUL$
