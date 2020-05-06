#include "topology.h"

#include <string.h>

int main() {

  char *topo_fname = "tests/test.topo";
  struct topology_t *pt = topology_load(topo_fname, strlen(topo_fname));

  /* 10 Mbps switches */
  topology_init_switches(pt, 1000);
  topology_init_links(pt, 2, 0.65);
}
