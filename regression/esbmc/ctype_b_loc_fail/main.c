#include <assert.h>

extern const unsigned short int **__ctype_b_loc(void);

int main()
{
  /* '_' is punctuation (1 << 2), not alphanumeric (1 << 3). */
  assert((*__ctype_b_loc())['_'] & (1 << 3));
  return 0;
}
// Imported from ESBMC regression/esbmc/ctype_b_loc_fail
// EXPECT: ^VERIFICATION FAILED$
// EXPECT: ^  assertion \(\*__ctype_b_loc\(\)\)\[.*\] & \(1 << 3\)$
// Vereda: unmet EXPECT: ^  assertion \(\*__ctype_b_loc\(\)\)\[.*\] & \(1 << 3\)$
// MODE: FUTURE
