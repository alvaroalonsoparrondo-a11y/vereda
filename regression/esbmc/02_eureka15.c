
int main(){
  int x,i;
  x=5;
  x=__VERIFIER_nondet_int();
  while(x<4){    
    if(x>0){
      x=x+1;  
    } else {
      x=1;
    }
  }
 L: assert(0);
}
// Imported from ESBMC regression/esbmc/02_eureka15
// RUN: --unwind 5
// EXPECT: ^VERIFICATION FAILED$
