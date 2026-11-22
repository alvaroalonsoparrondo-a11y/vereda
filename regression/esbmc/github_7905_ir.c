// #7905: under --ir a vector bitcast between lanes of one width converts each
// lane's value, as a scalar bitcast there does.
#include <assert.h>

typedef int v4i __attribute__((__vector_size__(16)));
typedef unsigned v4u __attribute__((__vector_size__(16)));

int __VERIFIER_nondet_int(void);

int main(void)
{
  v4i c = {__VERIFIER_nondet_int(), 1, 2, 3};
  v4u d = (v4u)c;
  assert(d[1] == 1u && d[3] == 3u);
  return 0;
}
// Imported from ESBMC regression/esbmc/github_7905_ir
// Needs: --ir
// RUN: --ir
// MODE: FUTURE
// EXPECT: ^VERIFICATION SUCCESSFUL$
