#include <assert.h>
#include <string.h>

static size_t my_strnlen(const char *s, size_t n)
{
  const char *p = memchr(s, 0, n);
  return p ? (size_t)(p - s) : n;
}

int main(void)
{
  char name[4] = "abc";
  assert(my_strnlen(name, 64) == 3);
  assert(memchr(name, 'a', 64) == name);
  assert(memchr(name, 'c', 3) == name + 2);
  assert(memchr(name, 'z', 4) == NULL);
  return 0;
}
// Imported from ESBMC regression/cstd/github_9439
// RUN: -m64 --unwind 20
// EXPECT: ^VERIFICATION SUCCESSFUL$
