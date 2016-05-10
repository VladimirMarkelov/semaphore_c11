#include "threads.h"
#include "ringbuffer.h"

int ring_buffer_init(ring_buffer_t* rbuf, unsigned int count) {
    if (rbuf == NULL) {
        return 2;
    }

    if (count == 0) {
        return 1;
    }

    rbuf->count = count;
    sem_init(&rbuf->sem_count, 0);
    sem_init(&rbuf->sem_space, 16);
    mtx_init(&rbuf->mtx, mtx_plain);

    return 0;
}

void ring_buffer_destroy(ring_buffer_t* rbuf) {
    if (rbuf == NULL) {
        return;
    }

    if (rbuf->count > 0) {
        sem_destroy(&rbuf->sem_count);
        sem_destroy(&rbuf->sem_space);
        mtx_destroy(&rbuf->mtx);
    }
}

void ring_push(ring_buffer_t* rbuf, void* value) {
    if (rbuf == NULL || rbuf->count == 0) {
        return;
    }

    sem_wait(&rbuf->sem_space);
    mtx_lock(&rbuf->mtx);
    rbuf->buffer[rbuf->counter] = value;
    rbuf->counter = (rbuf->counter+1) % 16;
    mtx_unlock(&rbuf->mtx);
    sem_post(&rbuf->sem_count);
}

void* ring_pop(ring_buffer_t* rbuf) {
    if (rbuf == NULL || rbuf->count == 0) {
        return 0;
    }

    sem_wait(&rbuf->sem_count);

    mtx_lock(&rbuf->mtx);
    rbuf->counter = (rbuf->counter+15) % 16;
    void* value = rbuf->buffer[rbuf->counter];
    mtx_unlock(&rbuf->mtx);
    sem_post(&rbuf->sem_space);

    return value;
}
