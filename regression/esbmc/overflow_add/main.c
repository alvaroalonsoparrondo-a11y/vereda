#include <limits.h>

int main()
{
  int a = INT_MAX, b = 1;
  int add_overflow = a + b; // Undefined behavior
  return 0;
}
// Imported from ESBMC regression/esbmc/overflow_add
// Needs: --overflow-check
// RUN: --overflow-check --z3
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
