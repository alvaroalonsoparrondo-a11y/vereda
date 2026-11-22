unsigned int nondet_uint();

int main()
{
  unsigned int n = nondet_uint();
  unsigned int x=n, y=0;
  while(x>0)
  {
    x--;
    y++;
  }
  assert(y==n);
}

// Imported from ESBMC regression/k-induction-parallel/count_up_down
// Needs: --k-induction-parallel
// RUN: --k-induction-parallel
// MODE: KNOWNBUG
// EXPECT: ^VERIFICATION SUCCESSFUL$
