#include <stdlib.h>

typedef struct
{
  int p;
} T;

int main(void)
{
  T *t = malloc(sizeof(T));
  if (!t)
    return 0;

  t->p = 1;

  int v = nondet_int();
  if (v != 0)
  {
    t->p = 2;
  }

  /* The join must keep both versions reachable, not just the branch's. */
  __VERIFIER_assert(t->p == 1 || t->p == 2); // both join arms survive

  int w = nondet_int();
  if (w != 0)
  {
    t->p = 3;
  }
  else
  {
    t->p = 3;
  }
  __VERIFIER_assert(t->p == 3); // written on every path

  free(t);
  return 0;
}
// Imported from ESBMC regression/esbmc/github_6798_ok
// RUN: --unwind 4
// EXPECT: ^VERIFICATION SUCCESSFUL$
