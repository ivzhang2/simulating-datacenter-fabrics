#ifndef TRACE_H
#define TRACE_H

#include "packet.h"

#include <assert.h>

struct trace_t {
  struct packet_t **pparr;
  size_t n_pparr;
};

#endif /* TRACE_H */
