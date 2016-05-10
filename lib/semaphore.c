#include <pthread.h>
#include "semaphore.h"

int sem_init(sem_t* sem, int count) {
    if (sem == NULL) {
        return thrd_error;
    }

    if (count < 0) {
        count = 0;
    }
    sem->count = count;

    int res = mtx_init(&sem->mtx, mtx_plain);
    if (res == thrd_success) {
        res = cnd_init(&sem->cv);
    }

    return res;
}

void sem_destroy(sem_t* sem) {
    if (sem == NULL) {
        return;
    }

    mtx_destroy(&sem->mtx);
    cnd_destroy(&sem->cv);
}

void sem_post(sem_t* sem) {
    if (sem == NULL) {
        return;
    }

    mtx_lock(&sem->mtx);

    ++sem->count;
    cnd_signal(&sem->cv);

    mtx_unlock(&sem->mtx);
}

void sem_wait(sem_t* sem) {
    if (sem == NULL) {
        return;
    }

    mtx_lock(&sem->mtx);

    while (sem->count == 0) {
        cnd_wait(&sem->cv, &sem->mtx);
    }

    --sem->count;

    mtx_unlock(&sem->mtx);
}

