int __VERIFIER_nondet_int(void);
int main()
{
  /* ~b + C becomes (C - 1) - b; C - 1 must not wrap at C = INT_MIN. */
  int b = __VERIFIER_nondet_int();
  __VERIFIER_assume(b >= 0 && b <= 10);
  int y = ~b + (-2147483647 - 1);
  __VERIFIER_assert(y > 0); // y > 0
  return 0;
}
// Imported from ESBMC regression/ir-ra/github_10537_bitnot_plus_int_min_fail
// Needs: --ir
// RUN: --ir --z3
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
// EXPECT: y > 0
