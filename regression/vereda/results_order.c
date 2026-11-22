// The results list shows the checks the solver decided. Assertions are
// decided first, so here the loop's check, which comes first in the walk,
// is never decided and must not be listed.
// RUN: --unwind 3
// EXPECT: FAILED +\[main\.assertion\.1\]
// EXPECT: 1 of 1 properties failed
// EXPECT-NOT: main\.unwind\.0
extern void __VERIFIER_assert(int);
extern int nondet(void);
int main(void) {
  int n = nondet(), s = 0;
  for (int i = 0; i < n; i++)
    s++;
  __VERIFIER_assert(s != 1);
  return 0;
}
