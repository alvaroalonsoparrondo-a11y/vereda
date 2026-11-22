#include <stddef.h>

struct P
{
  int a;
  int b;
};

int main()
{
  unsigned n = (unsigned)offsetof(struct P, b);
  int s = 0;
  for (unsigned i = 0; i < n; i++)
    s++;
  __ESBMC_assert(s == 9, "b does not sit nine bytes into the struct");
  return 0;
}
// Imported from ESBMC regression/esbmc/offsetof_loop_bound_fail
// RUN: --unwind 6
// EXPECT: ^VERIFICATION FAILED$
// EXPECT: b does not sit nine bytes into the struct
// Vereda: unmet EXPECT: ^VERIFICATION FAILED$
// MODE: FUTURE
