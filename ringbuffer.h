#ifndef _RINGBUFFER_H

#include <stdint.h>
#include <stdio.h>
#include <errno.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct ringbuffer {
	int32_t* buffer;
	int head;
	int tail;
	int max;
	int count;
	bool full;
} ringbuffer_t;

typedef ringbuffer_t* ringbuffer_h;

ringbuffer_h ringbuffer_init(int size);
int ringbuffer_push(ringbuffer_h ring, int32_t value);
int ringbuffer_pop(ringbuffer_h ring, int32_t *value);
int ringbuffer_empty(ringbuffer_h ring);
int ringbuffer_full(ringbuffer_h ring);
int ringbuffer_remaining(ringbuffer_h ring);
int ringbuffer_destroy(ringbuffer_h);

#endif
