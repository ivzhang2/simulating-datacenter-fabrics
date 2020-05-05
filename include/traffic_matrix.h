#ifndef _TRAFFIC_MATRIX_H
#define _TRAFFIC_MATRIX_H

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

/**
 * object for the traffic mattrix,
 * includes data on the list of nodes and its size,
 * and whether or not it is cumulative/normalized
 */
struct traffic_matrix_t {
  double *lst;
  size_t n_nodes;

  bool cumulative;
  bool normalized;
};

/**
 * Initialize a traffic matrix object,
 * given the size (number of nodes)
 */
struct traffic_matrix_t *traffic_matrix_init(const size_t n_nodes);

/**
 * Free the memory utilize by the traffic matrix object
 */
void traffic_matrix_free(struct traffic_matrix_t *pm);

/**
 * Read the traffic from given file
 * and store the data in the initialized traffic matrix object
 */
struct traffic_matrix_t *traffic_matrix_from_file(const char *filename,
                                                  const size_t n_filename);
/**
 * Set the source and destination using random sampling for traffic simulation
 */
void traffic_matrix_sample(struct traffic_matrix_t *pm, size_t *src,
                           size_t *dst, unsigned int *pseed);

#endif /* _TRAFFIC_MATRIX_H */
