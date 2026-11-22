#include <limits.h>

int main()
{
  int g = INT_MIN, h = -1;
  int div_overflow = g / h; // Undefined behavior
  return 0;
}
// Imported from ESBMC regression/esbmc/overflow_div
// Needs: --overflow-check
// RUN: --overflow-check --z3
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
