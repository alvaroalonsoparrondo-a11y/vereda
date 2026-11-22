#include <limits.h>

int main()
{
  unsigned int ui = 1, uj = 2;
  unsigned int mod_wrap = ui % uj;
  return 0;
}
// Imported from ESBMC regression/esbmc/overflow_mod2
// Needs: --unsigned-overflow-check
// RUN: --unsigned-overflow-check --z3
// MODE: FUTURE
// EXPECT: ^VERIFICATION SUCCESSFUL$
