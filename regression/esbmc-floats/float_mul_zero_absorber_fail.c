#include <assert.h>
#include <math.h>

float nondet_float(void);

int main()
{
  float i = nondet_float();
  __VERIFIER_assume(isinf(i));
  assert(i * 0.0f == 0.0f);
  return 0;
}
// Imported from ESBMC regression/floats/float_mul_zero_absorber_fail
// EXPECT: ^VERIFICATION FAILED$
// Vereda: unmet EXPECT: ^VERIFICATION FAILED$
// MODE: FUTURE
