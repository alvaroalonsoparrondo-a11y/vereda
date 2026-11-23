// What clang cannot settle at compile time is "unknown" at run time, as
// LLVM's back end lowers it: an object size -1 (0 for its minimum), and
// __builtin_constant_p false.
// EXPECT: ^VERIFICATION SUCCESSFUL$
#include <stddef.h>
extern void __VERIFIER_assert(int);
extern int __VERIFIER_nondet_int(void);
int main(void) {
  char *p;
  __VERIFIER_assert(__builtin_object_size(p, 0) == (size_t)-1);
  __VERIFIER_assert(__builtin_object_size(p, 2) == 0);
  int n = __VERIFIER_nondet_int();
  __VERIFIER_assert(!__builtin_constant_p(n));
  return 0;
}
