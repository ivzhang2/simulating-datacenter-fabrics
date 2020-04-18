#ifndef _TRAFFIC_MATRIX_H
#define _TRAFFIC_MATRIX_H

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

struct traffic_matrix_t {
  double *lst;
  size_t n_nodes;

  bool cumulative;
  bool normalized;
};

struct traffic_matrix_t *traffic_matrix_init(const size_t n_nodes);

void traffic_matrix_free(struct traffic_matrix_t *pm);

struct traffic_matrix_t *traffic_matrix_from_file(const char *filename,
                                                  const size_t n_filename);

void traffic_matrix_sample(struct traffic_matrix_t *pm, size_t *src,
                           size_t *dst);

#endif /* _TRAFFIC_MATRIX_H */
