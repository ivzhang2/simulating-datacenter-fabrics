#ifndef TOPOLOGY_H
#define TOPOLOGY_H

#include "network_object.h"

/**
* Object for the network topology 
* includes data on how many switches, how many links, and how many servers are in the topology
*/
struct topology_t {
  struct network_object_t **switches;
  size_t n_switches;

  struct network_object_t **links;
  size_t n_links;

  struct network_object_t **servers;
  size_t n_servers;
};

/**
* Create the appropriate topology from the given data in the input file
*/
struct topology_t *topology_load(const char *filename, const size_t n_filename);

/**
* Export the toplogy to a dot file, for visualization
*/
void topology_export_to_dot(const struct topology_t *topo, const char *filename,
                            const size_t n_filename);

/**
* Added data for switches in the topology
*/
void topology_init_switches(struct topology_t *pt, double microsec_line_rate);

/**
* Added data for links in the topology
*/
void topology_init_links(struct topology_t *pt, double link_length,
                         double material_factor);
#endif /* TOPOLOGY_H */
