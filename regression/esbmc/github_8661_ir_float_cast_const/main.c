// #8661: the simplifier folds a constant operand of the cast-overflow check
// and must agree with the SMT lowering that (int)-1.5 fits in an int.
int main(void)
{
  double d = -1.5;
  int z = (int)d;
  return z;
}
// Imported from ESBMC regression/esbmc/github_8661_ir_float_cast_const
// Needs: --ir --overflow-check
// RUN: --ir --overflow-check
// MODE: FUTURE
// EXPECT: ^VERIFICATION SUCCESSFUL$
