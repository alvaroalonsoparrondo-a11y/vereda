int nondet_int();

int main() {

  int x=nondet_int();
  __ESBMC_assume(x>0);
  int y=nondet_int();
  __ESBMC_assume(y>=0);
  __ESBMC_assume(y<x);
  int z=0;

  while(x>0) {
      x--;
      if(x==y) z=1; // assert(0);
  }
  assert(z==1);
}

// Imported from ESBMC regression/k-induction-parallel/check_if
// Needs: --k-induction-parallel
// RUN: --k-induction-parallel
// MODE: KNOWNBUG
// EXPECT: ^VERIFICATION SUCCESSFUL$
