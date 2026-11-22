int nondet_int();

int main() {

  int x=nondet_int();
  __VERIFIER_assume(x>0);
  int y=nondet_int();
  __VERIFIER_assume(y>=0);
  __VERIFIER_assume(y<1);
  int z=0;

  while(x>0) {
      x--;
      if(x==y) z=1; // assert(0);
  }
  assert(z==0);
}

// Imported from ESBMC regression/k-induction-parallel/check_if_bug
// Needs: --k-induction-parallel
// RUN: --k-induction-parallel -Wno-error=implicit-function-declaration
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
