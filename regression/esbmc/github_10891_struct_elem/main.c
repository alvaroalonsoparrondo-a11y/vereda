/* #10891 */
#include <assert.h>
#include <stdint.h>
unsigned nondet_uint(void);
struct MU { uint32_t value; };
struct __attribute__((packed)) Unaligned { uint32_t v; };
int main(void)
{
  struct MU buf[2] = {{7}, {7}};
  unsigned i = nondet_uint();
  __ESBMC_assume(i < 2);
  struct Unaligned r = *(struct Unaligned *)&buf[i];
  assert(r.v == 7);
  return 0;
}
// Imported from ESBMC regression/esbmc/github_10891_struct_elem
// EXPECT: ^VERIFICATION SUCCESSFUL$
// Vereda: unmet EXPECT: ^VERIFICATION SUCCESSFUL$
// MODE: FUTURE
