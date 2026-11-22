// #10316: Z3 aborted on ROUND_TO_AWAY under a symbolic rounding mode.
extern int __ESBMC_rounding_mode;
int __VERIFIER_nondet_int(void);

int main()
{
  __ESBMC_rounding_mode = __VERIFIER_nondet_int();
  // 1 + 2^-24 is a tie: ties-away gives 1 + 2^-23, ties-even gives 1.
  float x = 1.0f + 0x1p-24f;
  if (__ESBMC_rounding_mode == 1)
    __VERIFIER_assert(x == 1.0f + 0x1p-23f); // ties round away from zero
  return 0;
}
// Imported from ESBMC regression/z3/github_10316
// RUN: --solver z3
// EXPECT: ^VERIFICATION SUCCESSFUL$
// EXPECT: PASSED.*ties round away from zero
// Vereda: unmet EXPECT: ^VERIFICATION SUCCESSFUL$
// MODE: FUTURE
