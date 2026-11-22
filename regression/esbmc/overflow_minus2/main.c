#include <assert.h>

int main()
{
  int resp, a, b;

  resp=a-b;

  assert(resp==a-b);
}
// Imported from ESBMC regression/esbmc/overflow_minus2
// Needs: --overflow-check
// RUN: --overflow-check --z3
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
