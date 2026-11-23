#include <stdlib.h>

int main()
{
  unsigned int uc = 0, ud = 1;
  unsigned int sub_wrap = uc - ud;
  return 0;
}
// Imported from ESBMC regression/esbmc/overflow_sub
// Needs: --unsigned-overflow-check
// RUN: --unsigned-overflow-check --z3
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
