int __VERIFIER_nondet_int();

/* C11 6.5.5p6: / truncates toward zero and % takes the dividend's sign. */
int main(void)
{
  int a = __VERIFIER_nondet_int(), b = __VERIFIER_nondet_int();
  __VERIFIER_assume((a == 7 || a == -7) && (b == 2 || b == -2));
  int q = (a < 0) == (b < 0) ? 3 : -3;
  int r = a < 0 ? -1 : 1;
  __VERIFIER_assert(a / b == q); // quotient truncates toward zero
  __VERIFIER_assert(a % b == r); // remainder takes the dividend's sign
  __VERIFIER_assert(a == (a / b) * b + a % b); // C11 6.5.5p6 identity
  int c = __VERIFIER_nondet_int();
  __VERIFIER_assume(c == -6);
  __VERIFIER_assert(c / b == (b < 0 ? 3 : -3) && c % b == 0); // exact division
  return 0;
}
// Imported from ESBMC regression/esbmc/github_8662_ir_div_mod
// Needs: --ir
// RUN: --ir --multi-property
// MODE: FUTURE
// EXPECT: ^VERIFICATION SUCCESSFUL$
