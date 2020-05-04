#ifndef FLOW_H
#define FLOW_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/**
* An object for the flow in the form of a linked list.
* The object contains the flow size, the cdf distribution of the flow, and the next flow 
*/
struct flow_node_t {
  float flowsize;
  float cdf;
  struct flow_node_t *next;
};

/**
* Add the next flow to the current flow object (append node to the linked list)
*/
void append(struct flow_node_t **head_ref, int new_flowsize, float new_cdf);

/**
* Print the list of the flow object (linked list)
*/
void print_list(struct flow_node_t *node);

/**
* Given the file (with data about the distribution of the flow), 
* this function will read the flow from the given CDF distribution 
*/
struct flow_node_t *init_flow(char *filename);

/**
* Generate a random flow size according to the CDF, using inverse CDF method 
*/
float get_next_flow(struct flow_node_t *node);

/**
* Free the memory utlized by the flow object (linked list)
*/
void flow_free(struct flow_node_t *node);

#endif /* FLOW_H */
