#include <stdlib.h>

struct S {
  int x;
  struct S *n;
};

int main(int argc, char *argv[]) {
  int *p, *q, i=__VERIFIER_nondet_int();

  p = &i;
  
  argc=__VERIFIER_nondet_int();

  if (argc > 1) {
    q = &i;
  } else {
    q = p;
  }
  
  assert(*(p) + *(q) == 2*i);
  
}
