float nondet_float();

int main()
{
  float x = nondet_float();
  assert(x==x);
  return 0;
}
// Imported from ESBMC regression/esbmc/github_536_boolector
// Needs: --smt-model --boolector
// RUN: --smt-model --boolector -Wno-error=implicit-function-declaration
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
