#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// R4: the local header should be the first one to be include in order to
// prevent dependencies from being hidden.

#include "flow.h"

/* Append node to linked list  */
void append(struct FlowNode **head_ref, int new_flowsize, float new_cdf) {
  struct FlowNode *new_node =
      (struct FlowNode *)malloc(sizeof(struct FlowNode));
  struct FlowNode *last = *head_ref;

  new_node->flowsize = new_flowsize;
  new_node->cdf = new_cdf;

  new_node->next = NULL;

  if (*head_ref == NULL) {
    *head_ref = new_node;
    return;
  }

  while (last->next != NULL)
    last = last->next;

  last->next = new_node;
  return;
}

/* Print linked list */
void printList(struct FlowNode *node) {
  while (node != NULL) {
    printf("%f ", node->flowsize);
    printf("%f\n", node->cdf);
    node = node->next;
  }
}

/* Read flow CDF from file */
struct FlowNode *init_flow(char *filename) {
  char num_bytes[16];
  char prob[16];

  /* Flowsize distribution stored as linked list */
  struct FlowNode *flow_dist = NULL;

  FILE *fp = fopen(filename, "r");

  /* assumes no number exceeds length of 16 */
  while (fscanf(fp, " %16s", num_bytes) == 1) {
    int n = strtof(num_bytes, NULL);
    fscanf(fp, " %16s", prob);
    float p = strtof(prob, NULL);
    append(&flow_dist, n, p);
  }
  fclose(fp);
  return flow_dist;
}

/* Generate a random flow size according to the CDF */
float get_next_flow(struct FlowNode *node) {
  if (node == NULL) {
    printf("Flow size distribution has not been loaded\n");
    exit(0);
  }
  float r = ((float)rand() / (RAND_MAX));

  while (node->cdf < r) {
    node = node->next;
  }
  return node->flowsize;
}
