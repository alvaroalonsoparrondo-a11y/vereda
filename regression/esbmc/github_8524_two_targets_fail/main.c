#include <assert.h>
#include <stdio.h>

int main(void)
{
  char b[100];
  char x[3] = "ab";
  char y[5] = "abcd";
  char *p = nondet_int() ? x : y;

  int r = sprintf(b, "%s", p);
  assert(r == 2);
  return 0;
}
// Imported from ESBMC regression/esbmc/github_8524_two_targets_fail
// EXPECT: ^VERIFICATION FAILED$
// EXPECT: ^\s*FAILED\s+\[main\.assertion\.\d+\]\s+line 12\s+assertion r == 2$
// Vereda: unmet EXPECT: ^\s*FAILED\s+\[main\.assertion\.\d+\]\s+line 12\s+assertion r == 2$
// MODE: FUTURE
