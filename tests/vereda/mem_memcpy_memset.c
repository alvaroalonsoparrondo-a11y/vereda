// memset and memcpy with constant sizes, including an overlapping memmove.
// EXPECT: ^VERIFICATION SUCCESSFUL$
#include <string.h>
extern void __VERIFIER_assert(int);

int main(void) {
  char a[8];
  memset(a, 7, sizeof a);
  char b[8];
  memcpy(b, a, sizeof b);
  b[0] = 1;
  memmove(b + 1, b, 4);
  __VERIFIER_assert(a[3] == 7 && b[0] == 1 && b[1] == 1 && b[2] == 7 && b[7] == 7);
  return 0;
}
