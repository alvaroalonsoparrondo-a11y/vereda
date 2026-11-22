// --dump-smt-too prints the formula and then solves as usual, each check on
// its own.
// RUN: --dump-smt-too --unwind 2
// EXPECT: ^\(assert
// EXPECT: ^\(check-sat\)
// EXPECT: SUCCESS +\[main\.assertion\.1\]
// EXPECT: FAILED +\[main\.assertion\.2\]
// EXPECT: VERIFICATION FAILED
extern void __VERIFIER_assert(int);
extern int nondet(void);
int main(void) {
  int x = nondet();
  __VERIFIER_assert(x == x);
  __VERIFIER_assert(x != 7);
  return 0;
}
