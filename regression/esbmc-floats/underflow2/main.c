#include <assert.h>

int main() 
{
  double x = 1e-200, y = 1e-200;
  double result1 = x * y;        // Underflows to 0.0
  assert(result1 > 0.0);         // FAILS - underflow
  return 0;
}
// Imported from ESBMC regression/floats/underflow2
// Needs: --ir
// RUN: --ir
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
