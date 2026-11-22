#include <assert.h>

int nondet_int();

int main()
{
  int x = nondet_int();
  __VERIFIER_assume(x > 5);
  assert(x > 5);
  return 0;
}
// Imported from ESBMC regression/esbmc/assert_description_holds
// EXPECT: ^VERIFICATION SUCCESSFUL$
