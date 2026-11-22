#include <pthread.h>
#include <assert.h>
int g;
void *t(void *arg)
{
  for (g = 0; g < 10; g++)
    ;
  return 0;
}
int main(void)
{
  pthread_t id;
  pthread_create(&id, 0, t, 0);
  assert(g != 5);
  return 0;
}
// Imported from ESBMC regression/esbmc/github_8712_shared_counter_fail
// RUN: --unwind 12
// EXPECT: ^VERIFICATION FAILED$
// EXPECT: ^\s*FAILED\s+\[main\.assertion\.1\]\s+line\s+14\s+assertion g != 5$
// Vereda: unmet EXPECT: ^VERIFICATION FAILED$
// MODE: FUTURE
