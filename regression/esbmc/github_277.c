long nondet_long(void);

int main(void) {
  long l = 0;
  int c = 0;
  long t = nondet_long();
  c += (l < t);
}
// Imported from ESBMC regression/esbmc/github_277
// Needs: --overflow-check
// RUN: --overflow-check
// MODE: FUTURE
// EXPECT: ^VERIFICATION SUCCESSFUL$
