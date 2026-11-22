int nondet_int();
int g;

int f(int a, int b)
{
  if (a)
    return 1;
  if (b)
    g++;
  return 0;
}

int main()
{
  f(nondet_int(), nondet_int());
  f(nondet_int(), nondet_int());
  __ESBMC_assert(g == 0, "g");
  return 0;
}
// Imported from ESBMC regression/witnesses_validate/reachsafety-violationwitness/branching_after_dead_return
// Needs: --validate-violation-witness --witness witness.yml
// RUN: --validate-violation-witness --witness witness.yml
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
