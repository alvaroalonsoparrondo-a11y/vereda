#include <assert.h>

unsigned char flag;

int main()
{
  flag = 0;
  /* Returns the OLD contents, so this is 0, not 1. */
  assert(__atomic_test_and_set(&flag, __ATOMIC_SEQ_CST) == 1);
  return 0;
}
// Imported from ESBMC regression/esbmc/github_7642_fail
// EXPECT: ^\s*FAILED\s+\[main\.assertion\.1\]\s+line\s+9\s+assertion __atomic_test_and_set\(&flag, __ATOMIC_SEQ_CST\) == 1$
// EXPECT: ^VERIFICATION FAILED$
// Vereda: unmet EXPECT: ^\s*FAILED\s+\[main\.assertion\.1\]\s+line\s+9\s+assertion __atomic_test_and_set\(&flag, __ATOMIC_SEQ_CST\) == 1$
// MODE: FUTURE
