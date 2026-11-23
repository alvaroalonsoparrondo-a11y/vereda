// glibc's <ctype.h> macros read the class and case tables of the C locale,
// for every value from EOF to 255. (Each read at a nondet index costs the
// solver about 2 s, so the test keeps to a few.)
// RUN: --unwind 2
// EXPECT: ^VERIFICATION SUCCESSFUL$
#include <ctype.h>
#include <stdio.h>
extern void __VERIFIER_assert(int);
extern void __VERIFIER_assume(int);
extern int __VERIFIER_nondet_int(void);
int main(void) {
  int c = __VERIFIER_nondet_int();
  __VERIFIER_assume(c >= EOF && c <= 255);
  __VERIFIER_assert(!!isdigit(c) == (c >= '0' && c <= '9'));
  __VERIFIER_assert(!isupper(c) || tolower(c) == c + 32);
  __VERIFIER_assert(!isxdigit('g') && isxdigit('F') && ispunct('!') && !isprint(127));
  return 0;
}
