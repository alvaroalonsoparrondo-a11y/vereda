#include <assert.h>

int main() {
  _ExtInt(1000) x = __VERIFIER_nondet_float();
  unsigned _ExtInt(1000) y = __VERIFIER_nondet_int();
  assert(x == (_ExtInt(1000)) y); 
}
// Imported from ESBMC regression/esbmc/bitvector_02
// Needs: REQUIRES bitint_wide
// RUN: 
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
// Vereda: FUTURE test passed unexpectedly; promote it to CORE
// MODE: CORE
