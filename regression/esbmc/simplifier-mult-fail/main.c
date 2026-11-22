#include <assert.h>

int main()
{
  int x = nondet_int();
  assert(x * (-1) == -x);
  return 0;
}
// Imported from ESBMC regression/esbmc/simplifier-mult-fail
// Needs: --overflow-check
// RUN: --overflow-check
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
