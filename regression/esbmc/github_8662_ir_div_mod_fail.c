int nondet_int();

int main(void)
{
  int a = nondet_int();
  __VERIFIER_assume(a == -7);
  __VERIFIER_assert(a / 2 == -4 || a % 2 == 1); // Euclidean rounding
  return 0;
}
// Imported from ESBMC regression/esbmc/github_8662_ir_div_mod_fail
// Needs: --ir
// RUN: --ir
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
// EXPECT: Euclidean rounding
