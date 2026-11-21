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
