// Through a pointer without a prototype clang calls with type (...); the
// targets are matched against the arguments actually passed.
// RUN: --unwind 2
// EXPECT: ^VERIFICATION FAILED$
// EXPECT: line 9
// EXPECT-NOT: __vereda_unknown_target
extern void __VERIFIER_assert(int);
static int twice(int x) { return 2 * x; }
static void check(int x) { __VERIFIER_assert(x != 4); }
int main(void) {
  int (*f)() = twice;
  void (*g)() = check;
  __VERIFIER_assert(f(3) == 6);
  g(4);
  return 0;
}
