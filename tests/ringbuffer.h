#include "semaphore.h"

typedef struct {
    sem_t sem_space;
    sem_t sem_count;
    mtx_t mtx;
    void* buffer[16];
    unsigned int count;
    unsigned int counter;
} ring_buffer_t;

int ring_buffer_init(ring_buffer_t* rbuf, unsigned int count);
void ring_buffer_destroy(ring_buffer_t* rbuf);
void ring_push(ring_buffer_t* rbuf, void* value);
void* ring_pop(ring_buffer_t* rbuf);
