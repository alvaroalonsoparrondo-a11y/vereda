extern float __VERIFIER_nondet_float(void);

int main(void)
{
  float x = __VERIFIER_nondet_float();
  /* Any nonzero x with |x| < 2^-74.5 has x*x < 2^-149 (float min subnormal),
   * so IEEE 754 rounds x*x to zero. */
  __VERIFIER_assume(x > 0.0f && x < 1e-22f);
  float y = x * x;
  __VERIFIER_assert(y != 0.0f); // float mul of tiny x underflows to zero
  return 0;
}
// Imported from ESBMC regression/ir-ra/ra-mul-subnormal-underflow-fail
// Needs: --ir-ieee
// RUN: --ir-ieee --z3
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
