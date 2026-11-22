int nondet_int();

int main() {

  int x=nondet_int();
  __VERIFIER_assume(x>0);
  int y=nondet_int();
  __VERIFIER_assume(y>=0);
  __VERIFIER_assume(y<x);
  int z=0;

  while(x>0) {
      x--;
      if(x==y) z=1; // assert(0);
  }
  assert(z==1);
}

// Imported from ESBMC regression/k-induction/check_if
// Needs: --k-induction
// RUN: --k-induction
// MODE: KNOWNBUG
// EXPECT: ^VERIFICATION SUCCESSFUL$
