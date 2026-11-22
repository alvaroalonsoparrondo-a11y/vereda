#include <limits.h>

int main()
{
  int e = INT_MAX, f = 3;
  int mul_overflow = e * f; // Undefined behavior
  return 0;
}
// Imported from ESBMC regression/esbmc/overflow_mul
// Needs: --overflow-check
// RUN: --overflow-check --z3
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
