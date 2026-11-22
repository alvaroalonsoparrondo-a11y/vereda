/* ptr_sound_old_wrong_dir_fail: (soundness)
 * ensures claims *p == old(*p) + 1 (increment), but body decrements.
 * Wrong direction: *p = *p - 1, so *p == old(*p) - 1, not +1.
 * Must be VERIFICATION FAILED.
 */
#include <stddef.h>

void f(int *p)
{
  __ESBMC_requires(p != NULL);
  __ESBMC_ensures(*p == __ESBMC_old(*p) + 1); /* claims increment */

  *p = *p - 1; /* actually decrements */
}

int main()
{
  int x = 10;
  f(&x);
  return 0;
}
// Imported from ESBMC regression/function_contract/ptr_sound_old_wrong_dir_fail
// Needs: --enforce-contract f
// RUN: --enforce-contract f
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
