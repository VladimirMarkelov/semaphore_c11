#ifndef SEMAPHORE_20160905
#define SEMAPHORE_20160905

#ifdef __cplusplus
extern "C" {
#endif

#include "threads.h"

typedef struct semaphore_t {
  mtx_t mtx;
  cnd_t cv;
  int count;

} sem_t;

int sem_init(sem_t* sem, int count);
void sem_destroy(sem_t* sem);
void sem_wait(sem_t* sem);
void sem_post(sem_t* sem);

#ifdef __cplusplus
}
#endif

#endif
