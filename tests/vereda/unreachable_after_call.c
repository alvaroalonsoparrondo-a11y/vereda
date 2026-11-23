// An ordinary call right before __builtin_unreachable: clang emits the same
// call-then-unreachable shape as for a noreturn call, but plain() returns,
// so this is still a failed check.
// EXPECT: ^  __builtin_unreachable$
// EXPECT: ^VERIFICATION FAILED$
extern int __VERIFIER_nondet_int(void);
extern void plain(void);

int main(void) {
  if (__VERIFIER_nondet_int()) {
    plain();
    __builtin_unreachable();
  }
  return 0;
}
