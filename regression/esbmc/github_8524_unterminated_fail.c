#include <assert.h>
#include <stdio.h>

int main(void)
{
  char b[100];
  char name[4] = {'A', 'B', 'C', 'D'};

  int r = sprintf(b, "%s", name);
  assert(r < 0);
  return 0;
}
// Imported from ESBMC regression/esbmc/github_8524_unterminated_fail
// EXPECT: ^VERIFICATION FAILED$
// EXPECT: ^\s*FAILED\s+\[main\.assertion\.\d+\]\s+line 10\s+assertion r < 0$
// Vereda: unmet EXPECT: ^\s*FAILED\s+\[main\.assertion\.\d+\]\s+line 10\s+assertion r < 0$
// MODE: FUTURE
