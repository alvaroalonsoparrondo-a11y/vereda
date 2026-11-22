#include <limits.h>

int main()
{
  int i = INT_MIN, j = -1;
  int mod_overflow = i % j; // Undefined behavior
  return 0;
}
// Imported from ESBMC regression/esbmc/overflow_mod
// Needs: --overflow-check
// RUN: --overflow-check --z3
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
