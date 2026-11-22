/* The inductive step proves the claim past the loop once it drops the paths
   the unwinding bound cuts out of the loop (esbmc/esbmc#1320). */
int nondet_int();
_Bool nondet_bool();
int x;

int main()
{
  x = nondet_int();
  do
  {
    if (nondet_bool())
      x--;
    else
      x -= 2;
  } while (x > 0);
  __VERIFIER_assert(x <= 0); // the loop leaves with x <= 0
  return 0;
}
// Imported from ESBMC regression/k-induction/github_1320_do_while
// Needs: --k-induction
// RUN: --k-induction
// MODE: FUTURE
// EXPECT: ^VERIFICATION SUCCESSFUL$
