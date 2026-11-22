#include <assert.h>
#include <limits.h>
#include <stdlib.h>

int nondet_int(void);
long nondet_long(void);

int main()
{
  int x = nondet_int();
  long y = nondet_long();
  __ESBMC_assume(x > INT_MIN && y > LONG_MIN);
  assert(abs(x) >= 0);
  assert(labs(y) >= 0);
  assert(__builtin_abs(x) == abs(x));
  return 0;
}
// Imported from ESBMC regression/esbmc/abs_overflow_check
// Needs: --overflow-check
// RUN: --overflow-check --multi-property
// MODE: FUTURE
// EXPECT: ^VERIFICATION SUCCESSFUL$
// EXPECT: ^\*\* 0 of 10 properties failed, 10 passed$
// EXPECT: PASSED\s+\[main.arithmetic-overflow.7\]\s+line 15\s+arithmetic overflow on abs
