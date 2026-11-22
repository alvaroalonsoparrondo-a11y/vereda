int nondet_int();
int main() {
  int i, j=nondet_int();
  i = 2147483640 ;
  i = i+j;
  return 0;
}
// Imported from ESBMC regression/esbmc/github_277_2
// Needs: --overflow-check
// RUN: --overflow-check
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
