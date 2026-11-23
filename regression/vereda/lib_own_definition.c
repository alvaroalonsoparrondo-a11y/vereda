// A program's own definition of a library function wins over the model
// (with a nondet string, so that clang does not fold the call), and time()
// returns any value, stored through its argument too.
// RUN: --unwind 2
// EXPECT: ^VERIFICATION SUCCESSFUL$
#include <stddef.h>
#include <time.h>
extern void __VERIFIER_assert(int);
extern char __VERIFIER_nondet_char(void);
size_t strlen(const char *s) { return s ? 42 : 0; }
int main(void) {
  char s[2] = {__VERIFIER_nondet_char(), 0};
  __VERIFIER_assert(strlen(s) == 42);
  time_t t;
  time_t now = time(&t);
  __VERIFIER_assert(t == now);
  return 0;
}
