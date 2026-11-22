#include <assert.h>
#include <math.h>

double nondet_double(void);

int main(void)
{
  double d = nondet_double();
  __VERIFIER_assume(d > 0);
  assert(signbit(-d) == 0);
  return 0;
}
// Imported from ESBMC regression/floats/signbit_neg_nondet_fail
// EXPECT: ^VERIFICATION FAILED$
// EXPECT: ^  assertion signbit\(-d\) == 0$
// Vereda: unmet EXPECT: ^VERIFICATION FAILED$
// MODE: FUTURE
