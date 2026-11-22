// #8055
int nondet_int();
int g;

int f(void)
{
  g = 0;
  return nondet_int();
}

int main()
{
  int i = 0;
  g = f();
  while (i < g)
  {
    i++;
    if (i > 3)
      break;
  }
  __ESBMC_assert(i == 0, "loop not entered");
}
// Imported from ESBMC regression/esbmc/github_8055_global
// EXPECT: ^VERIFICATION FAILED$
// Vereda: unmet EXPECT: ^VERIFICATION FAILED$
// MODE: FUTURE
