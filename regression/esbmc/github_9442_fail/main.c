#include <assert.h>
#include <pthread.h>

int main(void)
{
  pthread_key_t k;
  if (pthread_key_create(&k, 0) != 0)
    return 0;
  assert(pthread_setspecific(k, 0) != 0);
  return 0;
}
// Imported from ESBMC regression/esbmc/github_9442_fail
// RUN: -m64 --unwind 20
// EXPECT: ^VERIFICATION FAILED$
