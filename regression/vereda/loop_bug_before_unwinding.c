// A bug inside a loop that never ends is reported as the assertion, not as
// the unwinding assertion: assertions are checked first, as in ESBMC's
// incremental BMC.
// RUN: --unwind 5
// EXPECT: ^  FAILED       \[main\.assertion\.1\]  line 13  __VERIFIER_assert$
// EXPECT: ^VERIFICATION FAILED$
extern void __VERIFIER_assert(int);

int main(void) {
  int x = 0;
  while (1) {
    x++;
    __VERIFIER_assert(x < 3);
  }
}
