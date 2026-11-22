#include <assert.h>

int main(void)
{
  int x = nondet_int();
  __ESBMC_assume(x > 0 && x < 10);
  assert(x > 5);
  assert(x > 5);
  return 0;
}
// Imported from ESBMC regression/esbmc/proof_cache_reuse_fail
// Needs: --proof-cache proof-store --claim-fingerprint-dump fp.tsv CHECK_FILE fp.tsv contains SAT CHECK_FILE fp.tsv contains line\s8
// RUN: --multi-property --proof-cache proof-store --claim-fingerprint-dump fp.tsv
// MODE: FUTURE
// EXPECT: ^Proof cache: 0 claim\(s\) reused, 2 solved$
// EXPECT: ^\s+FAILED\s+\[main\.assertion\.2\]\s+line 8\s+assertion x > 5$
// EXPECT: ^VERIFICATION FAILED$
