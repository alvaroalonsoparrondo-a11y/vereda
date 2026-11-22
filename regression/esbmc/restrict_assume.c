#include <assert.h>
void f(void *restrict a, void *restrict b)
{
  __ESBMC_assume(a != 0);
  __ESBMC_assume(b != 0);
  assert(a != b);
}
// Imported from ESBMC regression/esbmc/restrict_assume
// Needs: --func f --restrict-assume
// RUN: --func f --restrict-assume
// MODE: FUTURE
// EXPECT: ^VERIFICATION SUCCESSFUL$
