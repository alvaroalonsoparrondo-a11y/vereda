// realloc keeps the old contents up to the smaller size; realloc(NULL, n)
// is malloc, realloc(p, 0) frees and returns null as glibc does, and a
// failed realloc leaves the old block alone.
// RUN: --unwind 6
// EXPECT: ^VERIFICATION SUCCESSFUL$
#include <stdlib.h>
extern void __VERIFIER_assert(int);
int main(void) {
  int *p = malloc(3 * sizeof(int));
  if (!p)
    return 0;
  p[0] = 7;
  p[2] = 9;
  int *q = realloc(p, 5 * sizeof(int));
  if (!q) {
    __VERIFIER_assert(p[0] == 7 && p[2] == 9);
    return 0;
  }
  __VERIFIER_assert(q[0] == 7 && q[2] == 9);
  q[4] = 1;
  int *r = realloc(q, sizeof(int));
  __VERIFIER_assert(!r || r[0] == 7);
  __VERIFIER_assert(realloc(r ? r : q, 0) == 0);
  int *s = realloc(0, sizeof(int));
  __VERIFIER_assert(!s || s != q);
  return 0;
}
