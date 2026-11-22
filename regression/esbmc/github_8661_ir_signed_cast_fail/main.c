// The dual of ../github_8661_ir_signed_cast: 2^32 + 5 does not fit in an int.
// The simplifier folds the constant cast with wrap-around to 5, so checking
// the cast's result rather than its source missed it (#8661).
int main(void)
{
  long y = 4294967301L;
  int z = (int)y;
  return z;
}
// Imported from ESBMC regression/esbmc/github_8661_ir_signed_cast_fail
// Needs: --ir --overflow-check
// RUN: --ir --overflow-check
// MODE: FUTURE
// EXPECT: ^  Cast arithmetic overflow on typecast$
// EXPECT: ^VERIFICATION FAILED$
