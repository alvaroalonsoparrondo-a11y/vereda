int nondet_int();

int main()
{
  int a = nondet_int();
  __ESBMC_assume(a % 2 == 0);
  if (a % 2)
  {
    ++a;
    __ESBMC_assert(0, "unreachable odd branch");
  }
  __ESBMC_assert(a % 2 == 0, "a is even here");
  return 0;
}
// Imported from ESBMC regression/goto-coverage/github_5747_2
// Needs: --assertion-coverage-claims
// RUN: --assertion-coverage-claims
// MODE: FUTURE
// EXPECT: UNREACHED: 'unreachable odd branch at file .*main.c line 10
// EXPECT: REACHED: 'a is even here at file .*main.c line 12
// EXPECT: Reached Assertion Instances: 1
// EXPECT: Assertion Instances Coverage: 50%
// EXPECT: ^COVERAGE ANALYSIS COMPLETE$
