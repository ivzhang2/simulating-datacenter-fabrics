#include "queue.h"

#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0

struct node
{
    long start_time;
    long wait_time;
    struct node *next;
};
typedef struct node node;

struct queue
{
    int count;
    node *front;
    node *rear;
};
typedef struct queue queue;

void initialize(queue *q)
{
    q->count = 0;
    q->front = NULL;
    q->rear = NULL;
}

void display(node *head)
{
    if(head == NULL)
    {
        printf("NULL\n");
    }
    else
    {
        printf("%d\n", head -> wait_time);
        display(head->next);
    }
}

int isempty(queue *q)
{
    return (q->rear == NULL);
}

// Returns the time at which the enqueued flow will leave the switch and enqueues the flow
long enqueue(queue *q, long start_time, long wait_time)
{
        node *tmp;
        tmp = malloc(sizeof(node));
        tmp->start_time = start_time;
        tmp->wait_time = wait_time;
        tmp->next = NULL;
        q->count++;
        if(!isempty(q))
        {
            q->rear->next = tmp;
            q->rear = tmp;
            long dequeue_time = q->front->start_time;
            node *cur_node = q->front;
            while (cur_node != NULL)
            {
                dequeue_time += cur_node->wait_time;
                cur_node = cur_node->next;
            }
            return dequeue_time;
        }
        else // First node in queue
        {
            q->front = q->rear = tmp;
            return start_time + wait_time;
        }
}

// Returns wait time of dequeued flow
int dequeue(queue *q)
{
    node *tmp;
    long n = q->front->wait_time;
    tmp = q->front;
    q->front = q->front->next;
    q->count--;
    free(tmp);
    return(n);
}

// Free entire queue
void free_queue(queue *q)
{
    node *n = q->front;
    while (n != NULL) {
        struct node *victim = n;
        n = n->next;
        free (victim);
    }
    if (n) free (n);
    if (q) free (q);
}