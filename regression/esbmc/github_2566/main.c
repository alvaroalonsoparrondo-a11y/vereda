#include <assert.h>

int main() 
{
  float a;
  double b = a * 0;
  assert(b);
  return 0;
}
// Imported from ESBMC regression/esbmc/github_2566
// Needs: --ir
// RUN: --z3 --ir
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
