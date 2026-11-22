extern float __VERIFIER_nondet_float(void);
int main()
{
  float x = __VERIFIER_nondet_float();
  __VERIFIER_assume(x >= 0.0f && x <= 1.0f);
  __VERIFIER_assert(x <= 2.0f); // x stays in range
  return 0;
}
// Imported from ESBMC regression/esbmc/ir-ieee-no-solver
// Needs: --ir-ieee
// RUN: --ir-ieee
// MODE: FUTURE
// EXPECT: ^VERIFICATION SUCCESSFUL$
// EXPECT: \bdefaulting to Z3\b
