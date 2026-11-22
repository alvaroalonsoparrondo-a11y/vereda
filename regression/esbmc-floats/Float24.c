int main()
{
  float a, b, _a=a, _b=b;
  __VERIFIER_assume(a==1 && b==2);
  assert(a!=b);
}
// Imported from ESBMC regression/floats/Float24
// Needs: --ir
// RUN: --floatbv --ir
// MODE: FUTURE
// EXPECT: ^Using integer\/real arithmetic mode; defaulting to Z3$
