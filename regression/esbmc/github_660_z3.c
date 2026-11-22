int main()
{
  double d = nondet_double();
  float f = d;
  assert(f == d);
}
// Imported from ESBMC regression/esbmc/github_660_z3
// Needs: --ir
// RUN: --ir --z3 -Wno-error=implicit-function-declaration
// MODE: FUTURE
// EXPECT: ^VERIFICATION SUCCESSFUL$
