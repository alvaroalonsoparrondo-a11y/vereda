// The string models: lengths, comparisons, copies and searches on strings
// with nondet contents.
// RUN: --unwind 8
// EXPECT: ^VERIFICATION SUCCESSFUL$
#include <string.h>
extern void __VERIFIER_assert(int);
extern char __VERIFIER_nondet_char(void);
int main(void) {
  char s[5] = {'a', __VERIFIER_nondet_char(), 'c', 0, 0};
  size_t n = strlen(s);
  __VERIFIER_assert(n == 1 || n == 3);
  __VERIFIER_assert((strcmp(s, "abc") == 0) == (s[1] == 'b'));
  __VERIFIER_assert(strncmp(s, "aXY", 1) == 0 && strncmp("ab", "ac", 2) < 0);
  char d[8];
  strcpy(d, s);
  __VERIFIER_assert(strcmp(d, s) == 0 && strlen(d) == n);
  strcat(d, "z");
  __VERIFIER_assert(strlen(d) == n + 1 && d[n] == 'z');
  __VERIFIER_assert(strchr("hello", 'l') == strrchr("hello", 'l') - 1);
  __VERIFIER_assert(strchr("hello", 'q') == 0 && strchr("hi", 0) != 0);
  __VERIFIER_assert(memcmp("abc", "abd", 3) < 0 && memcmp("abc", "abd", 2) == 0);
  __VERIFIER_assert(memchr("abc", 'c', 3) != 0 && memchr("abc", 'c', 2) == 0);
  return 0;
}
