int main()
{
  int resp, a, b;

  resp=a+b;

  assert(resp==a+b);
}
// Imported from ESBMC regression/esbmc/overflow_01_addition
// Needs: --overflow-check
// RUN: --overflow-check -Wno-error=implicit-function-declaration
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
