#ifndef TRACE_H
#define TRACE_H

#include "packet.h"

#include <assert.h>

struct trace_t {
  struct packet_t **pparr;
  size_t n_pparr;
};

struct trace_t *trace_load(const char *filename, const size_t n_filename);

void trace_free(struct trace_t *pt);
#endif /* TRACE_H */
