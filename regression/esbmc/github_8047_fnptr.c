// #8047: the assume in h narrows g in the shared interval domain; the merge
// after the function-pointer call must join the path through f back in.
int g;
int nondet_int();

int f(int y)
{
  return y;
}

int h(int y)
{
  __VERIFIER_assume(g == 7);
  return y;
}

int main()
{
  int c;
  g = nondet_int();
  int (*fp)(int) = c ? f : h;
  fp(0);
  __VERIFIER_assert(g > -7); // g above -7
}
// Imported from ESBMC regression/esbmc/github_8047_fnptr
// Needs: --interval-symex-assert
// RUN: --interval-symex-assert
// MODE: FUTURE
// EXPECT: ^ +FAILED .*line 23 +g above -7$
// EXPECT: ^VERIFICATION FAILED$
