// EXPECT: ^VERIFICATION FAILED$
// EXPECT: reach_false\.c:16:3\n  assertion fails
// EXPECT: ^Counterexample:$
// EXPECT: ^State 1 \S*reach_false\.c:12 function main\n  x = \d+$
// EXPECT: ^State 3 \S*reach_false\.c:15 function main\n  z = 42$
// The assertion fails: x in (0, 100), y > 5, x + y == 42.
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
