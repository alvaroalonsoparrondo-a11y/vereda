int main()
{
  double x = nondet_double();
  __VERIFIER_assume(x == 3.0);
  __VERIFIER_assert(x / 2.0 == 1.0); // real division
  return 0;
}
// Imported from ESBMC regression/cvc/ir_nondet_float_real_div_fail
// Needs: --ir --std=gnu89
// RUN: --ir --cvc5 --std=gnu89
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
// EXPECT: ^\s+real division$
