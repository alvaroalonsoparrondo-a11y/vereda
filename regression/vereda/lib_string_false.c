// A copied string compares equal to a literal only when the nondet byte
// matches it; the solver finds the other case.
// RUN: --unwind 8
// EXPECT: ^VERIFICATION FAILED$
// EXPECT: line 13
#include <string.h>
extern void __VERIFIER_assert(int);
extern char __VERIFIER_nondet_char(void);
int main(void) {
  char s[3] = {'o', __VERIFIER_nondet_char(), 0};
  char d[3];
  strcpy(d, s);
  __VERIFIER_assert(strcmp(d, "ok") == 0);
  return 0;
}
