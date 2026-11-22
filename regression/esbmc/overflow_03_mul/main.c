int main()
{
  int resp, a, b, c, d, resp1;

  resp=a*b;
  resp1=c*d;

  assert(resp==a*b);
}
// Imported from ESBMC regression/esbmc/overflow_03_mul
// Needs: --overflow-check
// RUN: --overflow-check -Wno-error=implicit-function-declaration
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
