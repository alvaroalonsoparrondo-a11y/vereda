// EXPECT: ^VERIFICATION SUCCESSFUL$
// Both assertions hold: x > 0 rules out x < 0, and x % 7 is never 7.
extern int __VERIFIER_nondet_int(void);
extern void __VERIFIER_assume(int);
extern void __VERIFIER_assert(int);

int main(void) {
  int x = __VERIFIER_nondet_int();
  __VERIFIER_assume(x > 0);
  __VERIFIER_assert(x >= 0);
  switch (x % 7) {
  case 7:
    __VERIFIER_assert(0);
    break;
  default:
    break;
  }
  return 0;
}
