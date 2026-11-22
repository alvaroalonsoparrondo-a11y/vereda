#include <limits.h>

int main(void)
{
  int x = INT_MAX;
  return x + 1;
}
// Imported from ESBMC regression/esbmc/cwe_overflow
// Needs: --overflow-check
// RUN: --overflow-check --incremental-bmc
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
// EXPECT: ^  arithmetic overflow on add$
// EXPECT: ^  CWE: CWE-190, CWE-191$
