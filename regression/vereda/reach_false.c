// EXPECT: ^VERIFICATION FAILED$
// EXPECT: ^\[Counterexample\]$
// EXPECT: ^State 1 file \S*reach_false\.c line 13 function main thread 0\n-+\n  x = \d+ \([01 ]{35}\)$
// EXPECT: ^State 3 file \S*reach_false\.c line 16 function main thread 0\n-+\n  z = 42 \(00000000 00000000 00000000 00101010\)$
// EXPECT: ^Violated property:\n  file \S*reach_false\.c line 17 column 3 function main\n  __VERIFIER_assert$
// EXPECT: ^  FAILED       \[main\.assertion\.1\]  line 17  __VERIFIER_assert$
// EXPECT: ^\*\* 1 of 1 properties failed$
extern int __VERIFIER_nondet_int(void);
extern void __VERIFIER_assume(int);
extern void __VERIFIER_assert(int);

int main(void) {
  int x = __VERIFIER_nondet_int();
  int y = __VERIFIER_nondet_int();
  __VERIFIER_assume(x > 0 && x < 100);
  int z = y > 5 ? x + y : x - y;
  __VERIFIER_assert(!(z == 42 && y > 5));
  return 0;
}
