#include <assert.h>
#include <stddef.h>
void *alloca(size_t size);
int main(void)
{
  void *p;
  for (int i = 0; i < 2; ++i)
  {
    p = alloca(sizeof(int));
    *(int *)p = i;
  }
  alloca(sizeof(int));
  assert(*(int *)p == 1);
  return 0;
}
// Imported from ESBMC regression/esbmc/github_8709_alloca_assign_scope
// RUN: --unwind 3
// EXPECT: ^VERIFICATION SUCCESSFUL$
