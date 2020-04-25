#ifndef TOPOLOGY_H
#define TOPOLOGY_H

#include "network_object.h"

struct topology_t {
  struct network_object_t **switches;
  size_t n_switches;

  struct network_object_t **links;
  size_t n_links;

  struct network_object_t **servers;
  size_t n_servers;
};

struct topology_t *topology_load(const char *filename, const size_t n_filename);

#endif /* TOPOLOGY_H */
