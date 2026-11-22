#include <assert.h>

int __VERIFIER_nondet_int();

int main()
{
  int x = __VERIFIER_nondet_int();
  assert(x > 5);
  return 0;
}
// Imported from ESBMC regression/esbmc/assert_description
// EXPECT: ^  assertion x > 5$
// EXPECT: ^VERIFICATION FAILED$
// Vereda: unmet EXPECT: ^  assertion x > 5$
// MODE: FUTURE
