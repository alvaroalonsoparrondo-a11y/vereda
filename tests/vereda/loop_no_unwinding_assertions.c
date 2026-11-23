// With --no-unwinding-assertions the bound is assumed: paths that would run
// a sixth iteration are cut, so the assertion after the loop is never reached.
// RUN: --unwind 5 --no-unwinding-assertions
// EXPECT: ^VERIFICATION SUCCESSFUL$
extern void __VERIFIER_assert(int);

int main(void) {
  int s = 0;
  for (int i = 0; i < 10; i++)
    s += 2;
  __VERIFIER_assert(s == 20);
  return 0;
}
