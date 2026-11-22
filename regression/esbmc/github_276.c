long nondet_long(void);
 
int main(void) {
  long l = 0;
  int c = 0;
  long t = nondet_long();
  long s = nondet_long();
  long *b = &s;
 
  l = (t + *b) & (0xffffffffL); 
  c += (l < t);
}

// Imported from ESBMC regression/esbmc/github_276
// Needs: --overflow-check
// RUN: --overflow-check
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
