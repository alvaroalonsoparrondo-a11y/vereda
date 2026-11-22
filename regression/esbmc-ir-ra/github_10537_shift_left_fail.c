int main()
{
  /* Under --ir, 1 << 31 is 2^31, not INT_MIN. */
  int x = 1;
  x = x << 31;
  __VERIFIER_assert(x < 0); // x < 0
  return 0;
}
// Imported from ESBMC regression/ir-ra/github_10537_shift_left_fail
// Needs: --ir
// RUN: --ir --z3
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
// EXPECT: x < 0
