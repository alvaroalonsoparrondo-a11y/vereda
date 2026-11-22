#include <assert.h>

int main()
{
  unsigned int i;
  i=0;
  
  float *p;
  p=(float *)&i;
  
  float f=*p;
  
  assert(f==0.1);
}
// Imported from ESBMC regression/esbmc/github_2573_1
// Needs: --ir
// RUN: --z3 --ir
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
