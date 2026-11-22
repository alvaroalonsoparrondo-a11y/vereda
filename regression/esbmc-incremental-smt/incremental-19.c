
#include <assert.h>
int nondet_int();
int main()
{
  int x = nondet_int(); // input
  int y = nondet_int(); // input
  int z = nondet_int(); // input
  int *r1 = &x;
  int *r2 = &y;
  while(z > 0)
  {
    int *tmp = r1;
    r1 = r2;
    r2 = tmp;
    z = z - 1;
  }
  assert(*r1 != x || *r1 != y);
}
// Imported from ESBMC regression/incremental-smt/incremental-19
// Needs: --smt-during-symex --smt-symex-assert --smt-symex-guard --k-induction --add-symex-value-sets
// RUN: --smt-during-symex --smt-symex-assert --smt-symex-guard --k-induction --add-symex-value-sets
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
