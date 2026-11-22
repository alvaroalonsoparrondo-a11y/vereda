// The value a moved global takes on one branch is still reachable.
// EXPECT: ^Violated property:\n  file \S*mem_merge_arith_false\.c line 21 column 3 function main\n  __VERIFIER_assert\n  g != 5$
// EXPECT: ^VERIFICATION FAILED$
extern int __VERIFIER_nondet_int(void);
extern void __VERIFIER_assume(int);
extern void __VERIFIER_assert(int);

int g = 6, h = 1;

int main(void) {
  int x = __VERIFIER_nondet_int();
  __VERIFIER_assume(x >= 1 && x <= 3);
  if (__VERIFIER_nondet_int()) {
    g = g * x;
    h = 2;
  } else if (__VERIFIER_nondet_int()) {
    g = g / x;
  } else {
    g = g % 4 + x;
  }
  __VERIFIER_assert(g != 5); // x == 3 on the last branch
  g = g * 2;
  __VERIFIER_assert(g >= 4 && g <= 36);
  return 0;
}
