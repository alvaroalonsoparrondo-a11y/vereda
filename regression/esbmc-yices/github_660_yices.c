int main()
{
  double d = __VERIFIER_nondet_double();
  float f = d;
  assert(f == d);
}
// Imported from ESBMC regression/yices/github_660_yices
// Needs: --ir --yices
// RUN: --ir --yices
// MODE: FUTURE
// EXPECT: ^VERIFICATION SUCCESSFUL$
