// The dual of ../github_8661_ir_float_cast: a value below INT_MIN does not
// fit in an int, so the lower bound of a signed cast is still checked.
double nondet_double();
int main(void)
{
  double d = nondet_double();
  __VERIFIER_assume(d > -3e9 && d < -2.5e9);
  int z = (int)d;
  return z;
}
// Imported from ESBMC regression/esbmc/github_8661_ir_float_cast_fail
// Needs: --ir --overflow-check
// RUN: --ir --overflow-check --multi-property
// MODE: FUTURE
// EXPECT: ^  FAILED +\[github_8661_ir_float_cast_fail\.cast-arithmetic-overflow.1\] +line 8 +Cast arithmetic overflow on typecast$
// EXPECT: ^VERIFICATION FAILED$
