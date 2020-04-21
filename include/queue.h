#ifndef header_queue
#define header_queue

#include <stdio.h>
#include <stdlib.h>

struct node
{
    long start_time;
    long wait_time;
    struct node *next;
};

struct queue
{
    int count;
    node *front;
    node *rear;
};

// Initialize a queue
void initialize(queue *q);

// Display the queue
void display(node *head);

// Is the queue empty
int isempty(queue *q);

// Returns the time at which the enqueued flow will leave the switch and enqueues the flow
long enqueue(queue *q, long start_time, long wait_time);

// Dequeues the next flow and returns its wait time
int dequeue(queue *q);

// Free entire queue
void free_queue(queue *q);

#endif