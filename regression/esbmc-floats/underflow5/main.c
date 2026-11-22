#include <assert.h>

int main()
{
  float z = 1e30f;
  float result2 = z * z;        // Overflows in single precision
  assert(result2 < 1e40f);      // FAILS - single precision overflow

  return 0;
}

// Imported from ESBMC regression/floats/underflow5
// Needs: --ir
// RUN: --ir
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
