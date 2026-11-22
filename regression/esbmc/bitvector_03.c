#include <assert.h>

int main() {
  _ExtInt(1000) x = nondet_float();
  unsigned _ExtInt(1000) y = nondet_int();
  assert(x == (typeof(x)) y);
}
// Imported from ESBMC regression/esbmc/bitvector_03
// Needs: REQUIRES bitint_wide
// RUN: 
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
// Vereda: FUTURE test passed unexpectedly; promote it to CORE
// MODE: CORE
