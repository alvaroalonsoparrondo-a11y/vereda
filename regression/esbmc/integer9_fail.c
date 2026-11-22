#include <limits.h>

int main() {
  unsigned int a = 1;
  // Unary negation of an unsigned int
  unsigned int result = -a;
  return 0;
}

// Imported from ESBMC regression/esbmc/integer9_fail
// Needs: --ir --unsigned-overflow-check
// RUN: --z3 --ir --unsigned-overflow-check
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
