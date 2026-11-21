// The assertion inside the callee fails on the second call: the property is
// reported in the callee, and both calls share one claim.
// EXPECT: ^Violated property:\n  file \S*call_false\.c line 11 column 3 function check\n  __VERIFIER_assert\n  x < 10$
// EXPECT: ^  FAILED       \[check\.assertion\.1\]  line 11  __VERIFIER_assert$
// EXPECT: ^VERIFICATION FAILED$
extern void __VERIFIER_assert(int);

int twice(int x) { return x + x; }

void check(int x) {
  __VERIFIER_assert(x < 10);
}

int main(void) {
  check(twice(2));
  check(twice(5));
  return 0;
}
