#include <assert.h>
#include <stdio.h>

int main()
{
  int x;
  int r = sscanf("abc", "%d", &x);
  assert(r == 1);
  return 0;
}
// Imported from ESBMC regression/esbmc/scanf_return_count_fail
// EXPECT: ^VERIFICATION FAILED$
// EXPECT: ^  assertion r == 1$
// Vereda: unmet EXPECT: ^  assertion r == 1$
// MODE: FUTURE
