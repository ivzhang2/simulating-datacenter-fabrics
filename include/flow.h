#ifndef FLOW_H
#define FLOW_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* A linked list node */
struct flow_node_t {
  float flowsize;
  float cdf;
  struct flow_node_t *next;
};

/* Append node to linked list  */
void append(struct flow_node_t **head_ref, int new_flowsize, float new_cdf);

/* Print linked list */
void print_list(struct flow_node_t *node);

/* Read flow CDF from file */
struct flow_node_t *init_flow(char *filename);

/* Generate a random flow size according to the CDF */
float get_next_flow(struct flow_node_t *node);

/* Free linked list */
void flow_free(struct flow_node_t *node);

#endif /* FLOW_H */
