int main() {
  int *p;
  unsigned o;
  unsigned int n=nondet_uint();
  
  __ESBMC_assume(n>=1);
  __ESBMC_assume(n<10000000);

  p=malloc(sizeof(int)*n);
  __ESBMC_assume(p);
  
  o=n-1;

  p[o]=0;

  free(p);
}
// Imported from ESBMC regression/cbmc/01_cbmc_Malloc1
// EXPECT: ^VERIFICATION SUCCESSFUL$
