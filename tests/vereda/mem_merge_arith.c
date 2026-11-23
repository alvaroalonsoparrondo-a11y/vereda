// A global whose branches multiply, divide or take a remainder goes to the
// arrays at the merge; reads after it see each branch's value, and a store
// after it makes the global known again.
// EXPECT: ^VERIFICATION SUCCESSFUL$
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
  __VERIFIER_assert(g >= 2 && g <= 18 && (h == 1 || g % 6 == 0));
  g = g * 2;
  __VERIFIER_assert(g >= 4 && g <= 36);
  return 0;
}
