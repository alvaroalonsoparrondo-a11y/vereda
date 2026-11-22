#define ARRAY_SIZE 4
#include "stdio.h"

int main()
{
    int temp;
    __ESBMC_assert(0, "foo");
   return 0;
}
// Imported from ESBMC regression/esbmc/github_654
// Needs: --cex-output output
// RUN: --cex-output output
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
