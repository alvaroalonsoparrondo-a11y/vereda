/* Companion to github_5387. The bug made the post-call path vacuous, which
 * discharges *any* assertion placed there -- so both this true assertion and
 * the false one next door reported SUCCESSFUL. Pinning both directions is what
 * distinguishes a vacuous continuation from a correctly evaluated one. */
extern int __VERIFIER_nondet_int(void);

int f(int n)
{
  if (n <= 1)
    return n;
  return f(n - 1);
}

int main(void)
{
  int n = __VERIFIER_nondet_int();
  __VERIFIER_assume(n == 2 || n == 3);
  int r = f(n);
  __VERIFIER_assert(r == 1); // f returns 1 for both admitted values
  return r;
}
// Imported from ESBMC regression/esbmc/github_5387_value
// RUN: --unwind 24
// EXPECT: ^VERIFICATION SUCCESSFUL$
