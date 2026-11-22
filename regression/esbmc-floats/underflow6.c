#include <assert.h>

int main()
{
  double a = 1e-200, b = 1e-200;
  double result3 = a * b;       // Underflows to 0.0
  assert(result3 > 0.0);        // FAILS - double precision underflow
  return 0;
}

// Imported from ESBMC regression/floats/underflow6
// Needs: --ir
// RUN: --ir
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
