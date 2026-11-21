// EXPECT: ^VERIFICATION FAILED$
// EXPECT: reach_false\.c:17:5\n  reach_error is reachable
// EXPECT: ^Counterexample:$
// EXPECT: ^State 1 \S*reach_false\.c:12 function main\n  x = \d+$
// EXPECT: ^State 3 \S*reach_false\.c:15 function main\n  z = 42$
// reach_error is reachable: x in (0, 100), y > 5, x + y == 42.
extern int __VERIFIER_nondet_int(void);
extern void __VERIFIER_assume(int);
extern void reach_error(void);

int main(void) {
  int x = __VERIFIER_nondet_int();
  int y = __VERIFIER_nondet_int();
  __VERIFIER_assume(x > 0 && x < 100);
  int z = y > 5 ? x + y : x - y;
  if (z == 42 && y > 5)
    reach_error();
  return 0;
}
