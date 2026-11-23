// Atomics in one thread: each read-modify-write returns the old value and
// stores the new one; a strong compare-exchange succeeds exactly when the
// values are equal, and writes back the value it found when not.
// RUN: --unwind 2
// EXPECT: ^VERIFICATION SUCCESSFUL$
#include <stdatomic.h>
extern void __VERIFIER_assert(int);
extern int __VERIFIER_nondet_int(void);
int main(void) {
  _Atomic int x = 6;
  int n = __VERIFIER_nondet_int();
  __VERIFIER_assert(atomic_fetch_add(&x, n) == 6 && x == 6 + n);
  atomic_store(&x, 12);
  __VERIFIER_assert(atomic_fetch_sub(&x, 2) == 12 && atomic_load(&x) == 10);
  __VERIFIER_assert(atomic_fetch_and(&x, 6) == 10 && x == 2);
  __VERIFIER_assert(atomic_fetch_or(&x, 5) == 2 && x == 7);
  __VERIFIER_assert(atomic_fetch_xor(&x, 3) == 7 && x == 4);
  __VERIFIER_assert(atomic_exchange(&x, 9) == 4 && x == 9);
  int y = 9;
  __VERIFIER_assert(__atomic_fetch_nand(&y, 12, __ATOMIC_SEQ_CST) == 9 && y == ~8);
  __VERIFIER_assert(__atomic_fetch_max(&y, n, __ATOMIC_SEQ_CST) == ~8 && y == (n > ~8 ? n : ~8));
  unsigned long long z = 5; // unsigned, so umin
  __VERIFIER_assert(__atomic_fetch_min(&z, 3, __ATOMIC_SEQ_CST) == 5 && z == 3);
  int expected = 9;
  __VERIFIER_assert(atomic_compare_exchange_strong(&x, &expected, 1) && x == 1);
  expected = 5;
  __VERIFIER_assert(!atomic_compare_exchange_strong(&x, &expected, 2) && expected == 1 && x == 1);
  atomic_thread_fence(memory_order_seq_cst);
  _Atomic(char) c = 'a';
  __VERIFIER_assert(atomic_exchange(&c, 'b') == 'a' && c == 'b');
  return 0;
}
