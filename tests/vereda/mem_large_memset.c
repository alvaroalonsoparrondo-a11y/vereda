// A fill past MaxBytes that is not of a whole object would be millions of
// byte stores; it is unsupported instead of a memory blow-up.
// RUN: --force-malloc-success
// EXPECT: ^VERIFICATION UNKNOWN: unsupported: a fill of 16777215 bytes, not of a whole object$
#include <stdlib.h>
#include <string.h>
int main(void) {
  unsigned char *p = malloc(16u << 20);
  memset(p + 1, 255, (16u << 20) - 1);
  return 0;
}
