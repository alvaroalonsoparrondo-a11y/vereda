int main()
{
  double x = 1.5;
  float y = 3.5;
  float z = x + y;
  double a = 5.0;
  assert(a != z);
}
// Imported from ESBMC regression/cvc/github_660_cvc_fail
// Needs: --ir --std=gnu89
// RUN: --ir --cvc5 --std=gnu89
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
