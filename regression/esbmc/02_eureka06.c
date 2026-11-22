int i;
int a[20];

int main(){
  i=0;
  i=__VERIFIER_nondet_int();
  if(i>0){
    while(i<20){
      a[i]=i;
      i=i+1;
    }
  } else {
  L: assert(0);
  }
}
// Imported from ESBMC regression/esbmc/02_eureka06
// RUN: --unwind 20
// EXPECT: ^VERIFICATION FAILED$
// Vereda: unmet EXPECT: ^VERIFICATION FAILED$
// MODE: FUTURE
