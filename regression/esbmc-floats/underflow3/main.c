#include <assert.h>

int main() 
{
  double z = 1e-200;
  double result2 = z + z;
  assert(result2 > 1e+309);      
  return 0;
}
// Imported from ESBMC regression/floats/underflow3
// Needs: --ir
// RUN: --ir
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
