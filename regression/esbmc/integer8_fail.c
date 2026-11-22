#include <limits.h>

int main() 
{
  int a = INT_MIN;
  // This operation results in signed integer overflow
  int result = -a;
  return 0;
}

// Imported from ESBMC regression/esbmc/integer8_fail
// Needs: --ir --overflow-check
// RUN: --z3 --ir --overflow-check
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
