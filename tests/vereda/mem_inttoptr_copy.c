// A pointer made from an integer, stored in memory and copied, reads back as
// itself (#75). calloc's object comes after the first conversion of 0x1234;
// had it been allowed to cover that address, the second conversion would
// point into it while the stored copy still points nowhere, and they would
// differ. The struct copy is the shape of esbmc/github_5393.
// EXPECT: ^VERIFICATION SUCCESSFUL$
#include <assert.h>
#include <stdlib.h>
#include <string.h>

struct s {
  void *a;
  int pad[4];
};

int main(void) {
  void *t[2];
  t[0] = (void *)0x1234;
  void **p = calloc(2, sizeof(void *));
  if (!p)
    return 0;
  memcpy(p, t, sizeof t);
  assert(p[0] == (void *)0x1234);

  struct s u;
  u.a = (void *)0x5678;
  struct s *q = calloc(1, sizeof(struct s));
  if (!q)
    return 0;
  *q = u;
  assert(q->a == (void *)0x5678);
  return 0;
}
