// #9782: case 1 skips j's initializer, so j is indeterminate there
#include <assert.h>
int __VERIFIER_nondet_int(void);
int main(void)
{
  switch (__VERIFIER_nondet_int())
  {
  case 0:
  {
    unsigned char j = 3;
  case 1:
    assert(j >= 3);
  }
  }
  return 0;
}
// Imported from ESBMC regression/esbmc/github_9782_switch_fail
// EXPECT: ^  FAILED +\[main.assertion.1\]  line 12  assertion j >= 3$
// EXPECT: ^VERIFICATION FAILED$
// Vereda: unmet EXPECT: ^  FAILED +\[main.assertion.1\]  line 12  assertion j >= 3$
// MODE: FUTURE
