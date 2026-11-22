int main()
{
  double x = 1.5;
  float y = 3.5;
  float z = x + y;
  double a = 5.0;
  assert(a != z);
}
// Imported from ESBMC regression/esbmc/github_660_z3_fail
// Needs: --ir
// RUN: --ir --z3 -Wno-error=implicit-function-declaration
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
