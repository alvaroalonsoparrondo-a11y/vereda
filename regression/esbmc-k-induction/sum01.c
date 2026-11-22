#define a (2)
int nondet_int();
int main()
{
  int i, n = nondet_int(), sn = 0;
  for (i = 1; i <= n; i++)
    sn = sn + a;

  assert(sn == n * a || sn == 0);
}
// Imported from ESBMC regression/k-induction/sum01
// Needs: --k-induction
// RUN: --k-induction
// MODE: KNOWNBUG
// EXPECT: ^VERIFICATION SUCCESSFUL$
