// EXPECT: ^VERIFICATION SUCCESSFUL$
// Neither reach_error is reachable: x > 0 rules out x < 0, and x % 7 is
// never 7.
extern int __VERIFIER_nondet_int(void);
extern void __VERIFIER_assume(int);
extern void reach_error(void);

int main(void) {
  int x = __VERIFIER_nondet_int();
  __VERIFIER_assume(x > 0);
  if (x < 0)
    reach_error();
  switch (x % 7) {
  case 7:
    reach_error();
    break;
  default:
    break;
  }
  return 0;
}
