#include <assert.h>
#include <float.h>

int main() {
  double x = DBL_TRUE_MIN; // Smallest positive subnormal double
  double y = 0.5;
  double z = x * y;

  assert(z > 0.0); // Fails: gradual underflow
  return 0;
}

// Imported from ESBMC regression/floats/underflow9
// Needs: --ir
// RUN: --ir
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
