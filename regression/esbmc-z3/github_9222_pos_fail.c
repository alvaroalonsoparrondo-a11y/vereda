// #9222: a signed product above INT_MAX is an overflow.
int nondet_int(void);
int main(void)
{
  int a = nondet_int(), b = nondet_int();
  __ESBMC_assume((a < 0 && b < 0) || (a > 0 && b > 0));
  return a * b;
}
// Imported from ESBMC regression/z3/github_9222_pos_fail
// Needs: --overflow-check
// RUN: --z3 --overflow-check
// MODE: FUTURE
// EXPECT: arithmetic overflow on mul
// EXPECT: ^VERIFICATION FAILED$
