float nondet_float();

int main()
{
  float x = nondet_float();
  assert(x==x);
  return 0;
}
// Imported from ESBMC regression/bitwuzla/github_536_bitwuzla
// Needs: --smt-model
// RUN: --smt-model --bitwuzla -Wno-error=implicit-function-declaration
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
