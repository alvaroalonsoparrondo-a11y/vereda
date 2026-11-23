// Only one of the targets breaks the assertion; the trace must take it.
// RUN: --unwind 2
// EXPECT: ^VERIFICATION FAILED$
// EXPECT: line 14
extern void __VERIFIER_assert(int);
extern int nondet(void);
static int g;
static void set1(void) { g = 1; }
static void set2(void) { g = 2; }
int main(void) {
  void (*f)(void) = nondet() ? set1 : set2;
  f();
  __VERIFIER_assert(g >= 1);
  __VERIFIER_assert(g != 2);
  return 0;
}
