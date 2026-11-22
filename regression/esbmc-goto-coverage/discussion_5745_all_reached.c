int nondet_int();

int main()
{
  int a = nondet_int();
  __ESBMC_assert(a == a, "a equals itself");
  if (a > 0)
    __ESBMC_assert(a > 0, "positive branch");
  else
    __ESBMC_assert(a <= 0, "non-positive branch");
}
// Imported from ESBMC regression/goto-coverage/discussion_5745_all_reached
// Needs: --assertion-coverage-claims
// RUN: --assertion-coverage-claims
// MODE: FUTURE
// EXPECT: Reached Assertion Instances: 3
// EXPECT: Unreached Asserts: 0
// EXPECT: Assertion Instances Coverage: 100%
// EXPECT: ^COVERAGE ANALYSIS COMPLETE$
