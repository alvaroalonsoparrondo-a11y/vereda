int nondet_int();

main()
{
  int x=nondet_int();
  int *p = &x;
 
  while(x<100) {
   (*p)++;
  }                       
  assert(0);    
  //  assert(array[0]>=menor);    
}

// Imported from ESBMC regression/k-induction-parallel/terminator_01_bug
// Needs: --k-induction-parallel
// RUN: --k-induction-parallel -Wno-error=implicit-function-declaration -Wno-error=implicit-int
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
