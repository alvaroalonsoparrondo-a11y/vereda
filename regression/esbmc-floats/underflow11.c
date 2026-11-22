#include <assert.h>
#include <float.h>

int main() {
  double small = DBL_MIN;
  double large = 1e+308;
  double result = small / large;

  assert(result > 0.0); // Likely underflows to subnormal or 0.0
  return 0;
}

// Imported from ESBMC regression/floats/underflow11
// Needs: --ir
// RUN: --ir
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
