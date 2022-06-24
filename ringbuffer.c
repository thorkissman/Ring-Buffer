#include "ringbuffer.h"

/*
 * ringbuffer_init
 *
 * Initialize a new int32_t ringbuffer with given size in elements
 *
 * @param size Size in elements
 *
 * @return ringbuffer handle or NULL on error
 */
ringbuffer_h ringbuffer_init(int size) {
	ringbuffer_h cbuf = NULL;
	cbuf = malloc(sizeof(ringbuffer_h) * sizeof(int));		//Allocates size of the ringbuffer struct times the size of integers for size to allow space for buffer
	cbuf->buffer = malloc(size * sizeof(int32_t));		//Allocates size of the buffer for ringbuffer
	cbuf->head = 0;		//Keeps track of which ring buffer cell is head
	cbuf->tail = 0;		//Keeps track of which ring buffer cell is tail
	cbuf->max = size;		//Sets max size of ring buffer by input of int size
	cbuf->count = 0;		//Used to count how many values have been pushed onto the ring buffer
	cbuf->full = false;		//Bool to signify if ring buffer is full

	if (size < 1) {			//If an invalid size is given, return NULL
		return NULL;
	}
	else {					//Otherwise, return the ringbuffer
		return cbuf;
	}
}

/*
 * ringbuffer_push
 *
 * Push a new int32 element onto the given ringbuffer
 *
 * @param ring  ringbuffer handle to add an element to
 * @param value int32 value to push
 * 
 * @return 0 on success, other on failure
 */
int ringbuffer_push(ringbuffer_h ring, int32_t value) {
	if (ring->full) {		//If the ringbuffer is full, do not push value onto it. In this instance the push is cancelled,
		return -1;			//instead of overwriting existing value.
	}
	else {
		ring->buffer[ring->head] = value;					//Set head of ringbuffer to given value
		ring->head = (ring->head + 1) % ring->max;			//Change value for head to one more than previous, while accounting for the max size of the buffer by using modulo
		ring->full = (ring->head == ring->tail);			//Every time a push is done, check if the ringbuffer is full
		ring->count += 1;									//Add to count every time a push is done.
		return 0;
	}
}

/*
 * ringbuffer_pop
 *
 * Pop a int32 element from the given ringbuffer
 *
 * @param ring  ringbuffer handle to add an element to
 * @param value pointer to int32 value populate with popped value
 * 
 * @return 0 on success, other on failure
 */
int ringbuffer_pop(ringbuffer_h ring, int32_t *value) {
	if (ring->count == 0) {								//If the ringbuffer is empty, don't attempt to pop a value, throw error
		return -1;										
	}
	else {												//Else, set value to whatever value is stored in the tail of the ringbuffer.
		*value = ring->buffer[ring->tail];				
		ring->tail = (ring->max + 1) % ring->max;		//Change value of tail to one more than previous, account for max by using modulo
		ring->count -= 1;								//Decrease count of ringbuffer by one every time a value is popped
		ring->full = false;								//If a value is popped, it is not a full ringbuffer.
		return 0;
	}
}

/*
 * ringbuffer empty
 *
 * Check if a ringbuffer is empty
 * 
 * @param ring ringbuffer to check
 *
 * @return 0 if empty, 1 if non-empty, negative on failure
 */
int ringbuffer_empty(ringbuffer_h ring) {
	if (ring->count > 0) {							//If count is above zero, ringbuffer is not empty.
		return 1;
	}
	else if (ring->count == 0) {						//If count is zero, ringbuffer is empty
		return 0;
	}
	else {											//If count is somehow negative, fails.
		return -1;
	}
}

/*
 * ringbuffer full
 *
 * Check if a ringbuffer is full
 * 
 * @param ring ringbuffer to check
 *
 * @return 0 if full, 1 if non-full, negative on failure
 */
int ringbuffer_full(ringbuffer_h ring) {
	if (ring->full) {								//If bool full is true, return 0 for full
		return 0;
	}
	else if (!ring->full) {							//If false, return 1 for nonfull
		return 1;
	}
	else {											//If anything else, throw error
		return -1;
	}
}

/*
 * ringbuffer remaining
 *
 * Get count of remaining slots in ringbuffer
 * 
 * @param ring ringbuffer to check
 *
 * @return number of empty slots, negative on failure
 */
int ringbuffer_remaining(ringbuffer_h ring) {
	int remCount = ring->max - ring->count;				//Calculate how many spaces left by subtracting count of cells filled from max
	if (remCount > ring->max || remCount < 0) {			//If this number is over max or under zero, throw error
		return -1;
	}
	else {												//If it is valid, return.
		return remCount;
	}
}


/*
 * ringbuffer_destroy
 *
 * Destroy a given ringbuffer
 *
 * @param ring ringbuffer to destroy
 *
 * @return 0 on success, other on failure
 */
int ringbuffer_destroy(ringbuffer_h ring) {
	if (sizeof(ring) = 0) {						//If ring is empty, throw error
		return -1;
	}
	else if (sizeof(ring->buffer) <= 0) {		//If buffer is empty, throw error
		return -1;
	}
	free(ring->buffer);					//Otherwise, free buffer and then ring
	free(ring);

	return 0;
}
