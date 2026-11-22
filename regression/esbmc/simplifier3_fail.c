#include <assert.h>

int main() {
  int x = nondet_int();
  assert((x ^ x) != 0);
  return 0;
}

// Imported from ESBMC regression/esbmc/simplifier3_fail
// EXPECT: ^VERIFICATION FAILED$
