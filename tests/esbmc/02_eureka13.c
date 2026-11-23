int a[10];
int main(){
  int i,j;

  i=0;
  while(i<10){  
    if(i==5){
      i=a[i];
      L: assert(a[i]>0);
    } else {
      j=i;
    }
    i++;
  }
}

// Imported from ESBMC regression/esbmc/02_eureka13
// RUN: --unwind 10
// EXPECT: ^VERIFICATION FAILED$
