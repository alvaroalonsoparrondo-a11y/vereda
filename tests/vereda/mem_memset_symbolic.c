// A memset size with several possible values is not supported yet.
// EXPECT: ^VERIFICATION UNKNOWN: unsupported: llvm\.memset\.\S+ with a symbolic size$
#include <string.h>
extern unsigned __VERIFIER_nondet_uint(void);
extern void __VERIFIER_assume(int);

int main(void) {
  char buf[8];
  unsigned n = __VERIFIER_nondet_uint();
  __VERIFIER_assume(n >= 1 && n <= 4);
  memset(buf, 0, n);
  return buf[0];
}
