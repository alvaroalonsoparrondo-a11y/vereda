/* #10891 */
#include <stdint.h>
unsigned nondet_uint(void);
struct N { uint32_t v; };
int main(void)
{
  uint32_t buf[2] = {1, 2};
  unsigned o = nondet_uint();
  __ESBMC_assume(o <= 4);
  struct N r = *(struct N *)((unsigned char *)buf + o);
  return r.v;
}
// Imported from ESBMC regression/esbmc/github_10891_unpacked_align_fail
// EXPECT: ^  dereference failure: Incorrect alignment when accessing data object$
// EXPECT: ^VERIFICATION FAILED$
// Vereda: unmet EXPECT: ^  dereference failure: Incorrect alignment when accessing data object$
// MODE: FUTURE
