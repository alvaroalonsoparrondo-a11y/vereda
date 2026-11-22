int main()
{
  
  float a, b, c;

  a = nondet_float();
  b = nondet_float();

  if (nondet_bool())
    c = a + b;
  else
    c = a - b;

  assert(c==a+b || c==a-b);
}
// Imported from ESBMC regression/cbmc/01_cbmc_Fixedbv7
// Needs: --fixedbv
// RUN: --fixedbv -Wno-error=implicit-function-declaration
// MODE: FUTURE
// EXPECT: ^VERIFICATION SUCCESSFUL$
