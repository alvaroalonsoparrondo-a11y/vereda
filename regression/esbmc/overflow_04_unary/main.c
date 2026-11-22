int main()
{
  int resp, a;

  resp=-a;

  assert(resp==-a);
}
// Imported from ESBMC regression/esbmc/overflow_04_unary
// Needs: --overflow-check
// RUN: --overflow-check -Wno-error=implicit-function-declaration
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
