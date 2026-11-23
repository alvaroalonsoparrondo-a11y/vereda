// malloc may return null, as in ESBMC by default.
// EXPECT: ^  p != 0$
// EXPECT: ^VERIFICATION FAILED$
#include <stdlib.h>
extern void __VERIFIER_assert(int);

int main(void) {
  int *p = malloc(sizeof(int));
  __VERIFIER_assert(p != 0);
  return 0;
}
