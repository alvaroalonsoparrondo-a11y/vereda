/* Counterpart of zero_length_array_member_dyn_offset: the copy leaves the byte
 * after the header untouched, so asserting that it set that byte is
 * violated. */
#include <assert.h>
#include <stdlib.h>

struct s
{
  long a;
  long slots[0];
};

int main(void)
{
  unsigned i = nondet_uint();
  __VERIFIER_assume(i < 2);
  long *buf = calloc(4, sizeof(long));
  if (!buf)
    return 0;
  struct s tmpl;
  tmpl.a = 5;
  struct s *p = (struct s *)(buf + i);
  *p = tmpl;
  assert(buf[i + 1] == 5);
  free(buf);
  return 0;
}
// Imported from ESBMC regression/esbmc/zero_length_array_member_dyn_offset_fail
// RUN: -m64
// EXPECT: ^\s*FAILED\s+\[.*\]\s+line\s+[0-9]+\s+assertion buf\[i \+ 1\] == 5$
// EXPECT: ^VERIFICATION FAILED$
// Vereda: unmet EXPECT: ^\s*FAILED\s+\[.*\]\s+line\s+[0-9]+\s+assertion buf\[i \+ 1\] == 5$
// MODE: FUTURE
