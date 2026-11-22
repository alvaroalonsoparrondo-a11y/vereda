#include <assert.h>
#include <stdio.h>

int main(void)
{
  int r = putchar(300);
  assert(r != 44);
  return 0;
}
// Imported from ESBMC regression/esbmc/github_9440_fail
// RUN: -m64 --unwind 20
// EXPECT: ^VERIFICATION FAILED$
