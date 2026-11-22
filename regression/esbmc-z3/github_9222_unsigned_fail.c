// #9222: an unsigned product above UINT_MAX is an overflow.
unsigned nondet_uint(void);
int main(void)
{
  unsigned u = nondet_uint(), v = nondet_uint();
  __ESBMC_assume(u <= 65536 && v <= 65536);
  return (int)(u * v);
}
// Imported from ESBMC regression/z3/github_9222_unsigned_fail
// Needs: --unsigned-overflow-check
// RUN: --z3 --unsigned-overflow-check
// MODE: FUTURE
// EXPECT: ^\s+u = 65536
// EXPECT: ^\s+v = 65536
// EXPECT: arithmetic overflow on mul
// EXPECT: ^VERIFICATION FAILED$
