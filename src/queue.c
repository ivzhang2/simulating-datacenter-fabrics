#include "queue.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void initialize(struct queue_t* q)
{
    q->size_t = 0;
    q->front = NULL;
    q->rear = NULL;
}

void packet_display(struct packet* head)
{
    if(head == NULL)
    {
        printf("NULL\n");
    }
    else
    {
        printf("%d\n", head -> wait_time);
        packet_display(head->next);
    }
}

int isempty(struct queue_t* q)
{
    return (q->rear == NULL);
}

// Returns the time at which the enqueued flow will leave the switch and enqueues the flow
long queue_enqueue(struct queue_t* q, long start_time, long wait_time)
{
        struct packet* tmp;
        tmp = malloc(sizeof(struct packet));
        assert(tmp != NULL);
        tmp->start_time = start_time;
        tmp->wait_time = wait_time;
        tmp->next = NULL;
        q->size_t++;
        if(!isempty(q))
        {
            q->rear->next = tmp;
            q->rear = tmp;
            long dequeue_time = q->front->start_time;
            struct packet* cur_packet = q->front;
            while (cur_packet != NULL)
            {
                dequeue_time += cur_packet->wait_time;
                cur_packet = cur_packet->next;
            }
            return dequeue_time;
        }
        else // First packet in queue
        {
            q->front = q->rear = tmp;
            return start_time + wait_time;
        }
}

// Returns wait time of dequeued flow
int queue_dequeue(struct queue_t* q)
{
    struct packet* tmp;
    long n = q->front->wait_time;
    tmp = q->front;
    q->front = q->front->next;
    q->size_t--;
    free(tmp);
    return(n);
}

// Free entire queue
void queue_free(struct queue_t* q)
{
    struct packet* n = q->front;
    while (n != NULL) {
        struct packet *victim = n;
        n = n->next;
        free (victim);
    }
    if (n) free (n);
    if (q) free (q);
}