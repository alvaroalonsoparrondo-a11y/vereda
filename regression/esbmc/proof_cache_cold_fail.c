#include <assert.h>

int main(void)
{
  int x = nondet_int();
  __ESBMC_assume(x > 0 && x < 10);
  assert(x > 5);
  return 0;
}
// Imported from ESBMC regression/esbmc/proof_cache_cold_fail
// Needs: --proof-cache proof-store --claim-fingerprint-dump fp.tsv CHECK_FILE fp.tsv contains SAT
// RUN: --multi-property --proof-cache proof-store --claim-fingerprint-dump fp.tsv
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
