// The copy of mem_inttoptr_copy keeps its value, not just its equality to
// itself: the copied pointer differs from a neighbouring address (#75).
// EXPECT: ^VERIFICATION FAILED$
#include <assert.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
  void *t[2];
  t[0] = (void *)0x1234;
  void **p = calloc(2, sizeof(void *));
  if (!p)
    return 0;
  memcpy(p, t, sizeof t);
  assert(p[0] == (void *)0x1235);
  return 0;
}
