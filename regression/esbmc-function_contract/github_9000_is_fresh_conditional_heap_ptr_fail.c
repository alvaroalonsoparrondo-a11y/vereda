/* #9000: a pointer that may be &s or a heap object too small for struct P
 * does not satisfy is_fresh. */
#include <stdlib.h>
_Bool nondet_bool();
struct P
{
  int a;
  int b;
};
void g(struct P *d)
{
  __ESBMC_requires(__ESBMC_is_fresh(d, sizeof(struct P)));
  __ESBMC_ensures(1);
  d->b = 1;
}
int main()
{
  struct P s;
  struct P *d = nondet_bool() ? &s : malloc(sizeof(int));
  g(d);
  return 0;
}
// Imported from ESBMC regression/function_contract/github_9000_is_fresh_conditional_heap_ptr_fail
// Needs: --replace-call-with-contract g
// RUN: --replace-call-with-contract g --multi-property --force-malloc-success
// MODE: FUTURE
// EXPECT: ^ +FAILED.*contract requires$
// EXPECT: ^VERIFICATION FAILED$
