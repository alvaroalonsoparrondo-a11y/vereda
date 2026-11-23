#include <assert.h>

int main()
{
  int i;
  for (i = 0; i < 5; i++)
    ;
  assert(i == 5);
  return 0;
}
// Imported from ESBMC regression/esbmc/github_9498_counter
// RUN: --unwind 1 --no-unwinding-assertions
// EXPECT: ^VERIFICATION SUCCESSFUL$
