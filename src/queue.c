#include "queue.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void queue_init(struct queue_t* q)
{
    q->last_dequeue_time = 0;
}

// Enqueues the packet and returns the total time the packet will wait before it leaves the switch
long queue_enqueue(struct queue_t* q, struct packet* p)
{
    if (p->start_time >= q->last_dequeue_time){
        q->last_dequeue_time = p->start_time + p->wait_time;
    }
    else {
        q->last_dequeue_time += p->wait_time;
    }
    return q->last_dequeue_time - p->start_time;
}

void queue_free(struct queue_t* q)
{
    if (q) free (q);
}