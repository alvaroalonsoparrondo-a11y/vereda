#include <assert.h>

int main()
{
  int x = nondet_int();
  assert(x << 0 == x);
  return 0;
}
// Imported from ESBMC regression/esbmc/simplifier-shift-fail
// Needs: --ub-shift-check
// RUN: --ub-shift-check
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
