#include "flow.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Add the next flow to the current flow object (append node to the linked list)
 */
void append(struct flow_node_t **head_ref, int new_flowsize, float new_cdf) {
  struct flow_node_t *new_node =
      (struct flow_node_t *)malloc(sizeof(struct flow_node_t));
  struct flow_node_t *last = *head_ref;

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

/**
 * Print the list of the flow object (linked list)
 */
void print_list(struct flow_node_t *node) {
  while (node != NULL) {
    printf("%f ", node->flowsize);
    printf("%f\n", node->cdf);
    node = node->next;
  }
}

/**
 * Free the memory utlized by the flow object (linked list)
 */
void flow_free(struct flow_node_t *node) {
  while (node != NULL) {
    struct flow_node_t *victim = node;
    node = node->next;
    free(victim);
  }
  if (node)
    free(node);
}

/**
 * Given the file (with data about the distribution of the flow),
 * this function will read the flow from the given CDF distribution
 */
struct flow_node_t *init_flow(char *filename) {
  char num_bytes[16];
  char prob[16];

  /* Flowsize distribution stored as linked list */
  struct flow_node_t *flow_dist = NULL;

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

/**
 * Generate a random flow size according to the CDF, using inverse CDF method
 */
float get_next_flow(struct flow_node_t *node, unsigned int *pseed) {
  if (node == NULL) {
    printf("Flow size distribution has not been loaded\n");
    exit(0);
  }
  float r = ((float)rand_r(pseed) / (RAND_MAX));

  while (node->cdf < r) {
    node = node->next;
  }
  return node->flowsize;
}
