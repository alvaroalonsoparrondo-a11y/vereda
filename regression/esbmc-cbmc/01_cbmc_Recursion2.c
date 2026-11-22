void f(unsigned int counter) {
  if(counter==0) return;

  f(counter-1);
}

int main() {
  unsigned int x;
  __VERIFIER_assume(x<=10);
  
  f(x);

}
// Imported from ESBMC regression/cbmc/01_cbmc_Recursion2
// RUN: --no-unwinding-assertions --unwind 11
// EXPECT: ^VERIFICATION SUCCESSFUL$
