#include <stdio.h>
#include <stdint.h>
#include "ringbuffer.h"

int selftest() {
	ringbuffer_h ring;
	int32_t value;
	ring = ringbuffer_init(100000000);
	if (ring == NULL) {
		printf("ringbuffer_init returned null\n");
		return 1;
	}

	if (ringbuffer_push(ring, 1)) {
		printf("ringbuffer_push returned unsuccessful\n");
		return 1;
	}

	if (ringbuffer_pop(ring, &value)) {
		printf("ringbuffer_pop returned unsuccessful\n");
		return 1;
	}

	if (value != 1) {
		printf("Expected value 1, but got %d\n", value);
		return 1;
	}

	if (ringbuffer_empty(ring) != 0) {
		printf("Expected no values, got values\n");
		return 1;
	}

	if (ringbuffer_push(ring, 22)) {
		printf("ringbuffer_push returned unsuccessful\n");
		return 1;
	}

	if (ringbuffer_push(ring, 23)) {
		printf("ringbuffer_push returned unsuccessful\n");
		return 1;
	}

	if (ringbuffer_full(ring) == 0) {
		printf("Expected not full, got full\n");
		return 1;
	}

	ringbuffer_pop(ring, &value);

	printf("Value: %d\n", value);

	printf("Expected above 0, got %d\n", ringbuffer_remaining(ring));

	ringbuffer_destroy(ring);

	/*if (ringbuffer_destroy(ring) != -1) {
		printf("Expected empty, got empty\n");
		printf("Expected 0, got %d\n", ringbuffer_destroy(ring));
		return 0;
	}*/


	return 0;
}


int smoketest() {
	ringbuffer_h ring;
	int32_t value;

	ring = ringbuffer_init(10);
	if (ring == NULL) {
		printf("ringbuffer_init returned null\n");
		return 1;
	}

	if (ringbuffer_push(ring, 1)) {
		printf("ringbuffer_push returned unsuccessful\n");
		return 1;
	}

	if (ringbuffer_pop(ring, &value)) {
		printf("ringbuffer_pop returned unsuccessful\n");
		return 1;
	}

	if (value != 1) {
		printf("Expected value 1, but got %d\n", value);
		return 1;
	}

	return 0;
}
	
int main(int argc, char** argv) {
	return selftest();
}
