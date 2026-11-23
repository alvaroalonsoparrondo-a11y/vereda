// __builtin_*_overflow lowers to llvm.*.with.overflow: the result and the
// overflow bit are both encoded, signed and unsigned.
// EXPECT: ^VERIFICATION SUCCESSFUL$
#include <limits.h>
extern int __VERIFIER_nondet_int(void);
extern void __VERIFIER_assume(int);
extern void __VERIFIER_assert(int);

int main(void) {
  int x = __VERIFIER_nondet_int();
  __VERIFIER_assume(x == 65536);
  unsigned u;
  int ov = __builtin_umul_overflow((unsigned)x, (unsigned)x, &u);
  __VERIFIER_assert(ov && u == 0);
  int r;
  ov = __builtin_sadd_overflow(INT_MAX, x, &r);
  __VERIFIER_assert(ov && r == INT_MIN + x - 1);
  ov = __builtin_ssub_overflow(x, x + 2, &r);
  __VERIFIER_assert(!ov && r == -2);
  ov = __builtin_usub_overflow(0u, (unsigned)x, &u);
  __VERIFIER_assert(ov);
  return 0;
}
