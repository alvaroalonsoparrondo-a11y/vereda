#include <limits.h>

int main()
{
  int c = INT_MIN, d = 1;
  int sub_underflow = c - d; // Undefined behavior
  return 0;
}
// Imported from ESBMC regression/esbmc/overflow_minus5
// Needs: --overflow-check
// RUN: --overflow-check --z3
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
