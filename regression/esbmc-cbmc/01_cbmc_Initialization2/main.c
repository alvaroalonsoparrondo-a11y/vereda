int Test = nondet_int();

int f()
{
  return 1;
}

int g=f();

int main()
{
  assert(g==1);
}
// Imported from ESBMC regression/cbmc/01_cbmc_Initialization2
// EXPECT: ^ERROR: PARSING ERROR$
// Vereda: unmet EXPECT: ^ERROR: PARSING ERROR$
// MODE: FUTURE
