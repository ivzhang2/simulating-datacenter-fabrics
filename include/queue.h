#ifndef header_queue
#define header_queue

#include <stdio.h>
#include <stdlib.h>

struct packet
{
    long start_time;
    long wait_time;
    struct packet *next;
};

struct queue_t
{
    long last_dequeue_time;
};

// Initialize a queue
void queue_initialize(struct queue_t* q);

// Returns the time at which the enqueued flow will leave the switch and enqueues the packet
long queue_enqueue(struct queue_t* q, struct packet* p);

// Free entire queue
void queue_free(struct queue_t *q);

#endif