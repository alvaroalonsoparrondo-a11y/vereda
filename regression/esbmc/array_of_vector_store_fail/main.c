#include <assert.h>
extern int nondet_int(void);
__attribute__((__vector_size__(16))) int a[1] = {};
int main(void) {
  int c = nondet_int();
  if (c)
    a[0][0] = c;
  assert(a[0][0] == 0);
}
// Imported from ESBMC regression/esbmc/array_of_vector_store_fail
// EXPECT: ^VERIFICATION FAILED$
// Vereda: unmet EXPECT: ^VERIFICATION FAILED$
// MODE: FUTURE
