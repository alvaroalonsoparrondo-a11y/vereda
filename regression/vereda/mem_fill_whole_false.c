// A write at a nondet offset after a whole-object fill can hit the byte the
// assertion reads.
// RUN: --unwind 2 --force-malloc-success
// EXPECT: ^VERIFICATION FAILED$
// EXPECT: line 17
#include <stdlib.h>
#include <string.h>
extern void __VERIFIER_assert(int);
extern void __VERIFIER_assume(int);
extern unsigned __VERIFIER_nondet_uint(void);
int main(void) {
  unsigned char *p = malloc(4096);
  memset(p, 255, 4096);
  unsigned i = __VERIFIER_nondet_uint(), j = __VERIFIER_nondet_uint();
  __VERIFIER_assume(i < 4096 && j < 4096);
  p[j] = 0;
  __VERIFIER_assert(p[i] == 255);
  return 0;
}
