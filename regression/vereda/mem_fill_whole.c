// A fill of a whole large object (memset, calloc, a zeroed global) is one
// constant array of the object's own, so 16 MB costs nothing; later writes,
// at constant or nondet offsets, land on top of it.
// RUN: --unwind 2 --force-malloc-success
// EXPECT: ^VERIFICATION SUCCESSFUL$
#include <stdlib.h>
#include <string.h>
extern void __VERIFIER_assert(int);
extern void __VERIFIER_assume(int);
extern unsigned __VERIFIER_nondet_uint(void);
#define SIZE (16u << 20)
static int zeros[100000];
int main(void) {
  unsigned char *p = malloc(SIZE);
  memset(p, 255, SIZE);
  unsigned *q = calloc(SIZE / 4, 4);
  unsigned i = __VERIFIER_nondet_uint(), j = __VERIFIER_nondet_uint();
  __VERIFIER_assume(i < SIZE / 4 && j < SIZE / 4);
  __VERIFIER_assert(p[i] == 255 && q[i] == 0 && zeros[i % 100000] == 0);
  p[7] = 1;
  q[j] = 42;
  zeros[j % 100000] = 5;
  __VERIFIER_assert(p[7] == 1 && (i == 7 || p[i] == 255));
  __VERIFIER_assert(q[j] == 42 && (i == j || q[i] == 0));
  __VERIFIER_assert(zeros[j % 100000] == 5);
  return 0;
}
