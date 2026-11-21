// Recursion within the bound.
// RUN: --unwind 6
// EXPECT: ^VERIFICATION SUCCESSFUL$
extern void __VERIFIER_assert(int);

int fact(int n) { return n <= 1 ? 1 : n * fact(n - 1); }

int main(void) {
  __VERIFIER_assert(fact(5) == 120);
  return 0;
}
