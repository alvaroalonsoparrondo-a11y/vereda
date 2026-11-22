#include <assert.h>

int main()
{
  int x = nondet_int();
  int y = nondet_int();

  // (~x) == (~y) -> x == y
  assert(((~x) == (~y)) == (x == y));

  return 0;
}
// Imported from ESBMC regression/esbmc/simplifier19
// EXPECT: ^VERIFICATION SUCCESSFUL$
