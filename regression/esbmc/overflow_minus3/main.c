#include <assert.h>

int main()
{
  unsigned int resp, a, b;

  resp=a-b;

  assert(resp==a-b);
}
// Imported from ESBMC regression/esbmc/overflow_minus3
// Needs: --unsigned-overflow-check
// RUN: --unsigned-overflow-check --z3
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
