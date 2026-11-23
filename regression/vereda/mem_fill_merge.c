// An object filled on one path only, and a pointer that may be either of two
// filled objects: the join and the read choose arrays by object.
// RUN: --unwind 2 --force-malloc-success
// EXPECT: ^VERIFICATION SUCCESSFUL$
#include <stdlib.h>
#include <string.h>
extern void __VERIFIER_assert(int);
extern void __VERIFIER_assume(int);
extern unsigned __VERIFIER_nondet_uint(void);
extern int __VERIFIER_nondet_int(void);
int main(void) {
  unsigned char *a = malloc(2048), *b = malloc(2048);
  memset(a, 1, 2048);
  int c = __VERIFIER_nondet_int();
  if (c)
    memset(b, 2, 2048);
  else
    b[5] = 9;
  unsigned i = __VERIFIER_nondet_uint();
  __VERIFIER_assume(i < 2048);
  __VERIFIER_assert(!c || b[i] == 2);
  __VERIFIER_assert(c || b[5] == 9);
  unsigned char *q = __VERIFIER_nondet_int() ? a : b;
  q[i] = 3;
  __VERIFIER_assert(q[i] == 3);
  __VERIFIER_assert(q == b || a[i] == 3);
  __VERIFIER_assert(q == a || (i == 5 && !c) || b[i] == 3 || a[i] == 1);
  return 0;
}
