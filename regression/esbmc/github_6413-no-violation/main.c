#include <pthread.h>
#include <semaphore.h>

sem_t worker_done;
int shared;

void *worker(void *arg)
{
  int idx;
  for (idx = 0; idx < 2; ++idx)
  {
    shared = idx;
    __ESBMC_assert(1, "worker: in loop");
  }
  __ESBMC_assert(1, "worker: after loop");
  sem_post(&worker_done);
  return NULL;
}

int main()
{
  pthread_t thrd;
  sem_init(&worker_done, 0, 0);
  pthread_create(&thrd, NULL, worker, NULL);
  sem_wait(&worker_done);
  __ESBMC_assert(1, "main: after join");
  sem_destroy(&worker_done);
}
// Imported from ESBMC regression/esbmc/github_6413-no-violation
// RUN: --multi-property --unwind 4
// EXPECT: ^VERIFICATION SUCCESSFUL$
// EXPECT: ^ +PASSED .*line +13 +worker: in loop$
// EXPECT: ^ +PASSED .*line +15 +worker: after loop$
// EXPECT: ^ +PASSED .*line +26 +main: after join$
// EXPECT: \A(?![\s\S]*PASSED .*worker: in loop[\s\S]*PASSED .*worker: in loop)[\s\S]*\Z
// Vereda: unmet EXPECT: ^ +PASSED .*line +13 +worker: in loop$
// MODE: FUTURE
