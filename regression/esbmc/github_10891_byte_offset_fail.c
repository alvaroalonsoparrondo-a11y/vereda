/* #10891 */
#include <assert.h>
#include <stdint.h>
unsigned nondet_uint(void);
struct __attribute__((packed)) Unaligned { uint32_t v; };
int main(void)
{
  uint32_t buf[2] = {0x01020304u, 0x05060708u};
  unsigned o = nondet_uint();
  __VERIFIER_assume(o <= 4);
  struct Unaligned r = *(struct Unaligned *)((unsigned char *)buf + o);
  assert(o != 1 || r.v == 0x08010203u);
  assert(o != 3 || r.v == 0x06070801u);
  assert(r.v != 0x07080102u);
  return 0;
}
// Imported from ESBMC regression/esbmc/github_10891_byte_offset_fail
// RUN: --multi-property
// EXPECT: ^  PASSED +\[main.assertion.[0-9]+\] +line 12 +assertion o != 1 \|\| r.v == 0x08010203u$
// EXPECT: ^  PASSED +\[main.assertion.[0-9]+\] +line 13 +assertion o != 3 \|\| r.v == 0x06070801u$
// EXPECT: ^  FAILED +\[main.assertion.[0-9]+\] +line 14 +assertion r.v != 0x07080102u$
// EXPECT: ^VERIFICATION FAILED$
// Vereda: unmet EXPECT: ^  PASSED +\[main.assertion.[0-9]+\] +line 12 +assertion o != 1 \|\| r.v == 0x08010203u$
// MODE: FUTURE
