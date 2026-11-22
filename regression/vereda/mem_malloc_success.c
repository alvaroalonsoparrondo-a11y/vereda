// With --force-malloc-success, malloc never returns null.
// RUN: --force-malloc-success
// EXPECT: ^VERIFICATION SUCCESSFUL$
#include <stdlib.h>
extern void __VERIFIER_assert(int);

int main(void) {
  int *p = malloc(sizeof(int));
  __VERIFIER_assert(p != 0);
  return 0;
}
