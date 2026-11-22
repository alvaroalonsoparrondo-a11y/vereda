// --ir does not wrap the closed form's unsigned arithmetic: x started at -1.
int a[8]; int nondet_int();
int main(){ int n=nondet_int(); __VERIFIER_assume(n>0&&n<=8);
  int x=-1;
  for(int i=0;i<n;i++){ a[i]=0; x=x+1; }
  __VERIFIER_assert(x != n-1); }
// Imported from ESBMC regression/esbmc/array_loop_summary_ir
// Needs: --ir
// RUN: --ir
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
