// A memset whose size is loaded from memory but has one value on the path,
// as in uthash's bucket expansion: the solver settles the size.
// EXPECT: ^VERIFICATION SUCCESSFUL$
#include <string.h>
extern void __VERIFIER_assert(int);

struct table { unsigned buckets; };
struct table t = {3};

int main(void) {
  char buf[16];
  t.buckets *= 2;
  memset(buf, 1, t.buckets * 2);
  __VERIFIER_assert(buf[11] == 1);
  return 0;
}
