#include <assert.h>

int main() {
  int a = nondet_int();
  int b = nondet_int();

  __VERIFIER_assume(a > 0 && b > 0 && a > b);

  assert((a / b) > 0);
}
// Imported from ESBMC regression/esbmc/integer5
// Needs: --ir --overflow-check
// RUN: --z3 --ir --overflow-check
// MODE: FUTURE
// EXPECT: ^VERIFICATION SUCCESSFUL$
