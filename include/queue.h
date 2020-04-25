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
    int size_t;
    struct packet* front;
    struct packet* rear;
};

// Initialize a queue
void queue_initialize(struct queue_t* q);

// Display the queue
void queue_display(struct packet* head);

// Is the queue empty
int queue_isempty(struct queue_t* q);

// Returns the time at which the enqueued flow will leave the switch and enqueues the flow
long queue_enqueue(struct queue_t* q, long start_time, long wait_time);

// Dequeues the next flow and returns its wait time
int queue_dequeue(struct queue_t* q);

// Free entire queue
void queue_free(struct queue_t *q);

#endif