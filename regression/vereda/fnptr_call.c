// A call through a pointer that may hold either of two functions walks both,
// and the result is the chosen function's.
// RUN: --unwind 2
// EXPECT: ^VERIFICATION SUCCESSFUL$
extern void __VERIFIER_assert(int);
extern int nondet(void);
static int twice(int x) { return 2 * x; }
static int succ(int x) { return x + 1; }
int main(void) {
  int (*f)(int) = nondet() ? twice : succ;
  int r = f(3);
  __VERIFIER_assert(r == 6 || r == 4);
  __VERIFIER_assert(f == twice ? r == 6 : r == 4);
  return 0;
}
