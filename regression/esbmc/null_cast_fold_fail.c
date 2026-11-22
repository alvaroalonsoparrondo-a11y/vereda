/* A pointer that may be NULL keeps its claim. */
#include <stddef.h>

_Bool nondet_bool(void);
int x;

int main()
{
  int *p = nondet_bool() ? &x : NULL;
  __VERIFIER_assert(p != NULL); // p may be NULL
  return 0;
}
// Imported from ESBMC regression/esbmc/null_cast_fold_fail
// EXPECT: ^VERIFICATION FAILED$
