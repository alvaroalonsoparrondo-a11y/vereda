#include <limits.h>
#include <stdlib.h>

int nondet_int(void);

int main()
{
  int x = nondet_int();
  __VERIFIER_assume(x <= -2147483647);
  return abs(x);
}
// Imported from ESBMC regression/esbmc/abs_overflow_check_fail
// Needs: --overflow-check
// RUN: --overflow-check
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
// EXPECT: arithmetic overflow on abs
