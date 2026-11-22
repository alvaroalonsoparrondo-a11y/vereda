#include <assert.h>
int main()
{
  unsigned n = nondet_uint();
  char a[n];
  unsigned k = sizeof(a);
  assert(n == k);
}
// Imported from ESBMC regression/esbmc/github_588
// EXPECT: ^VERIFICATION FAILED$
// Vereda: unmet EXPECT: ^VERIFICATION FAILED$
// MODE: FUTURE
