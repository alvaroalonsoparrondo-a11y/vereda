void f(int counter) {
  if(counter==0) return;

  f(counter-1);
}

int main() {

  f(10);

}
// Imported from ESBMC regression/cbmc/01_cbmc_Recursion
// RUN: --unwind 11
// EXPECT: ^VERIFICATION SUCCESSFUL$
