int nondet_int();
int main() { 

  int fail=0;
  int x=nondet_int();
  __ESBMC_assume(x>0);
  while(x>0) {
    if(fail==1) {
      x= -1;
      fail=2;
    } else {
      x--;
    }
  }
  assert(x==0);
}

// Imported from ESBMC regression/k-induction/count_down
// Needs: --k-induction
// RUN: --k-induction
// MODE: KNOWNBUG
// EXPECT: ^VERIFICATION SUCCESSFUL$
