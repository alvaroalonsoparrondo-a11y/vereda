int main()
{
  double d = nondet_double();
  float f = d;
  assert(f == d);
}
// Imported from ESBMC regression/cvc/github_660_cvc
// Needs: --ir --std=gnu89
// RUN: --ir --cvc5 --std=gnu89
// MODE: FUTURE
// EXPECT: ^VERIFICATION SUCCESSFUL$
