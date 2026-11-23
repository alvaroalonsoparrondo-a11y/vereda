// A byte known on one side of a join only, next to an object that goes to
// the arrays at that join, keeps each side's value.
// EXPECT: ^VERIFICATION SUCCESSFUL$
extern int __VERIFIER_nondet_int(void);
extern void __VERIFIER_assume(int);
extern void __VERIFIER_assert(int);

int g = 6;
extern int k; // no initialiser: its bytes start in the arrays

int main(void) {
  int x = __VERIFIER_nondet_int();
  __VERIFIER_assume(x >= 1 && x <= 3);
  int b = __VERIFIER_nondet_int();
  int before = k;
  if (b) {
    g = g * x;
    k = 5;
  } else {
    g = g / x;
  }
  __VERIFIER_assert(b ? k == 5 && g % 6 == 0 : k == before && g >= 2);
  return 0;
}
