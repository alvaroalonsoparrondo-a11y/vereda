#include <assert.h>

int main() {
  unsigned u = nondet_uint();
  assert(u < 0);
  return 0;
}

// Imported from ESBMC regression/esbmc/simplifier2_fail
// EXPECT: ^VERIFICATION FAILED$
