#include <assert.h>
int g[4];
int main(void)
{
  int *p = &g[0];
  unsigned char k = nondet_uchar();
  __ESBMC_assume(k < 2);
  ((unsigned char *)&p)[k] = ((unsigned char *)&p)[k];
  assert(p == &g[0]);
  return 0;
}
// Imported from ESBMC regression/esbmc/github_7855-byte-update-sds
// Needs: --smt-during-symex
// RUN: --64 --smt-during-symex
// MODE: FUTURE
// EXPECT: ^VERIFICATION SUCCESSFUL$
