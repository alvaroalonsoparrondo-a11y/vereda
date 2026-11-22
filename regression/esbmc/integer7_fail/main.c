#include <limits.h>

int main() 
{
  int a = INT_MIN;
  int b = 1;
  // This operation results in signed integer overflow
  int result = a - b;
  return 0;
}

// Imported from ESBMC regression/esbmc/integer7_fail
// Needs: --ir --overflow-check
// RUN: --z3 --ir --overflow-check
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
