#include <limits.h>

int main()
{
  unsigned int ua = UINT_MAX, ub = 1;
  unsigned int add_wrap = ua + ub;
  return 0;
}
// Imported from ESBMC regression/esbmc/overflow_add2
// Needs: --unsigned-overflow-check
// RUN: --unsigned-overflow-check --z3
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
