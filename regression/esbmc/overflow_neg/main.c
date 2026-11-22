#include <limits.h>

int main()
{
  int k = INT_MIN;
  int neg_overflow = -k; // Undefined behavior
  return 0;
}
// Imported from ESBMC regression/esbmc/overflow_neg
// Needs: --overflow-check
// RUN: --overflow-check --z3
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
