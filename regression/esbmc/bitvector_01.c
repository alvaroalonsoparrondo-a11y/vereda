#include <assert.h>

int main() {
  _ExtInt(10) x = nondet_float();
  _ExtInt(10) y = nondet_int();
  assert(x == y);
}
// Imported from ESBMC regression/esbmc/bitvector_01
// EXPECT: ^VERIFICATION FAILED$
