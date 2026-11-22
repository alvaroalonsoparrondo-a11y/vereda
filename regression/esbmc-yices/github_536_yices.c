float nondet_float();

int main()
{
  float x = nondet_float();
  assert(x==x);
  return 0;
}
// Imported from ESBMC regression/yices/github_536_yices
// Needs: --smt-model --yices
// RUN: --smt-model --yices
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
