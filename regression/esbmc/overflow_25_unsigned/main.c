#include <stdio.h>
#include <assert.h>

int main(int argc, char **argv)
{
unsigned int delta = 0;
unsigned int i=5;
unsigned int j=3;

delta = j - i;
printf("\nDelta %u", delta);

return 0;
}
// Imported from ESBMC regression/esbmc/overflow_25_unsigned
// Needs: --unsigned-overflow-check
// RUN: --unsigned-overflow-check
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
