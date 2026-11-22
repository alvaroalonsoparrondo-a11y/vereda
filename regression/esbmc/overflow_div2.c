#include <limits.h>

int main()
{
  unsigned int ug = 1, uh = 2;
  unsigned int div_wrap = ug / uh;
  return 0;
}
// Imported from ESBMC regression/esbmc/overflow_div2
// Needs: --unsigned-overflow-check
// RUN: --unsigned-overflow-check --z3
// MODE: FUTURE
// EXPECT: ^VERIFICATION SUCCESSFUL$
