// The unreachable clang puts after a call that never returns only ends the
// path, for abort, a noreturn external and __builtin_trap alike (ESBMC also
// reports a reachable __builtin_trap as successful).
// EXPECT: ^VERIFICATION SUCCESSFUL$
#include <stdlib.h>
extern int __VERIFIER_nondet_int(void);
extern void die(void) __attribute__((noreturn));

int main(void) {
  int x = __VERIFIER_nondet_int();
  if (x == 1)
    abort();
  if (x == 2)
    die();
  if (x == 3)
    __builtin_trap();
  return 0;
}
