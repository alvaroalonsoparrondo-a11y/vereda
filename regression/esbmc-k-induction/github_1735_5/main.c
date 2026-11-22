#include <assert.h>

int main() {
  int x = nondet_int();
  __ESBMC_assume(x > 0);

start:
  x--;
  if (x == 0) goto end;
  goto check;

check:
  assert(x > 0); // This assertion always holds true
  goto start;

end:
  return 0;
}
// Imported from ESBMC regression/k-induction/github_1735_5
// Needs: --k-induction
// RUN: --k-induction
// MODE: FUTURE
// EXPECT: ^VERIFICATION UNKNOWN$
