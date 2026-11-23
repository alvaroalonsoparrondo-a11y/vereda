// A weak compare-exchange may fail although the values are equal, so the
// store is not certain.
// RUN: --unwind 2
// EXPECT: ^VERIFICATION FAILED$
// EXPECT: line 12
#include <stdatomic.h>
extern void __VERIFIER_assert(int);
int main(void) {
  _Atomic int x = 1;
  int expected = 1;
  atomic_compare_exchange_weak(&x, &expected, 2);
  __VERIFIER_assert(x == 2);
  return 0;
}
