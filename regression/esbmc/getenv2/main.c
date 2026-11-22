#include <stdlib.h>
#include <string.h>
#include <assert.h>

int main(void)
{
  char *result = getenv("");
  return 0;
}
// Imported from ESBMC regression/esbmc/getenv2
// RUN: --unwind 1
// EXPECT: ^VERIFICATION SUCCESSFUL$
