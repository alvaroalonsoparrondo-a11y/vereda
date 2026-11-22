#include <limits.h>

int main()
{
  unsigned int ue = UINT_MAX / 2, uf = 3;
  unsigned int mul_wrap = ue * uf;
  return 0;
}
// Imported from ESBMC regression/esbmc/overflow_mul2
// Needs: --unsigned-overflow-check
// RUN: --unsigned-overflow-check --z3
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
