#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* A linked list node */
struct FlowNode 
{ 
    float flowsize;
    float cdf; 
    struct FlowNode *next; 
};

/* Append node to linked list  */
void append(struct FlowNode** head_ref, int new_flowsize, float new_cdf);

/* Print linked list */ 
void printList(struct FlowNode *node);

/* Read flow CDF from file */
struct FlowNode* init_flow (char* filename);

/* Generate a random flow size according to the CDF */
float get_next_flow(struct FlowNode *node);