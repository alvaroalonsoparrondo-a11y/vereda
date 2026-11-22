#include <limits.h>

int main()
{
  unsigned int uk = 1;
  unsigned int neg_wrap = -uk;
  return 0;
}
// Imported from ESBMC regression/esbmc/overflow_neg2
// Needs: --unsigned-overflow-check
// RUN: --unsigned-overflow-check --z3
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
