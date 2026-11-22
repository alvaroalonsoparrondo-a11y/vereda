unsigned int nondet_uint();
int nondet_int();

#define SIZE 1

main()
{
  unsigned int j,k;
  int array[SIZE], menor;
  
  menor = nondet_int();

  for(j=0;j<SIZE;j++) {
       array[j] = nondet_int();
       
       if(array[j]<=menor)
          menor = array[j];                          
    }                       
    
    assert(array[0]>menor);    
}

// Imported from ESBMC regression/k-induction-parallel/array_bug
// Needs: --k-induction-parallel
// RUN: --k-induction-parallel -Wno-error=implicit-function-declaration -Wno-error=implicit-int
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
