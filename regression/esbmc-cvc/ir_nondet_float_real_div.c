int main()
{
  float f = nondet_float();
  double d = f;
  __VERIFIER_assert(d == f); // widening keeps the value
  return 0;
}
// Imported from ESBMC regression/cvc/ir_nondet_float_real_div
// Needs: --ir --std=gnu89
// RUN: --ir --cvc5 --std=gnu89
// MODE: FUTURE
// EXPECT: ^VERIFICATION SUCCESSFUL$
