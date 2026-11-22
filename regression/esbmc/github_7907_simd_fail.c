// #7907: the vector read back through a pointer to a nondeterministic
// element of an array of vectors is the one written there.
#include <assert.h>

typedef int v4i __attribute__((__vector_size__(16)));

int nondet_int(void);

int main(void)
{
  v4i a[3];
  int k = nondet_int();
  __ESBMC_assume(k >= 0 && k < 3);
  v4i *q = a + k;
  *q = (v4i){1, 2, 3, 4};
  v4i c = *q;
  assert(c[3] == 3);
  return 0;
}
// Imported from ESBMC regression/esbmc/github_7907_simd_fail
// EXPECT: ^VERIFICATION FAILED$
// EXPECT: ^.*assertion c\[3\] == 3$
// Vereda: unmet EXPECT: ^.*assertion c\[3\] == 3$
// MODE: FUTURE
