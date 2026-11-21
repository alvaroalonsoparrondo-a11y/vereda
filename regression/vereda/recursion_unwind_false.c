// Recursion deeper than the bound: the recursion unwinding assertion fails.
// RUN: --unwind 3
// EXPECT: ^Violated property:\n  file \S*recursion_unwind_false\.c line 8 column \d+ function fact\n  recursion unwinding assertion$
// EXPECT: ^VERIFICATION FAILED$
extern void __VERIFIER_assert(int);

int fact(int n) {
  return n <= 1 ? 1 : n * fact(n - 1);
}

int main(void) {
  __VERIFIER_assert(fact(5) == 120);
  return 0;
}
