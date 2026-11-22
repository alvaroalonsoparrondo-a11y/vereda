#include <assert.h>
struct S
{
  unsigned int x, y;
};
struct S s[2];
int main(void)
{
  int i = nondet_int();
  __ESBMC_assume(i >= 0 && i < 2);
  unsigned char *p = (unsigned char *)&s[i];
  *(unsigned long long *)p = 0x0000000200000001ULL;
  assert(s[i].x == 1);
  assert(s[i].y == 0);
  return 0;
}
// Imported from ESBMC regression/esbmc/struct_dyn_offset_spanning_flat_fail
// EXPECT: ^VERIFICATION FAILED$
// EXPECT: ^  assertion s\[i\]\.y == 0$
// Vereda: unmet EXPECT: ^  assertion s\[i\]\.y == 0$
// MODE: FUTURE
