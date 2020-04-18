// R1: add header guards to all .h files

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// R2: better naming: flow_node_t. To be more consistent with the libraries we
// use including the C standard library.

/* A linked list node */
struct FlowNode {
  float flowsize;
  float cdf;
  struct FlowNode *next;
};

/* Append node to linked list  */
void append(struct FlowNode **head_ref, int new_flowsize, float new_cdf);

// R3: print_list (see R2)

/* Print linked list */
void printList(struct FlowNode *node);

/* Read flow CDF from file */
struct FlowNode *init_flow(char *filename);

/* Generate a random flow size according to the CDF */
float get_next_flow(struct FlowNode *node);

// R5: create a flow_free function to free your heap allocated linked list
