#include <stdio.h>
#include <stdint.h>
#include "threads.h"
#include "ringbuffer.h"

int main (int argc, char** argv) {
    ring_buffer_t rb;

    ring_buffer_init(&rb, 16);
    int v = 4;
    ring_push(&rb, (void*)(uintptr_t)v);
    int x = (int)(uintptr_t)ring_pop(&rb);
    printf("Got value: %d\n", x);

    ring_buffer_destroy(&rb);

    return 0;
}
