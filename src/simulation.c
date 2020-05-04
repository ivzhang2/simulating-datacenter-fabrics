#include "topology.h"

/** 
* run the simulation
* build the tree topology based on the given structure in the .topo file
*/
int main() {
  struct topology_t *topo = topology_load("tests/test.topo", 15);
  topology_export_to_dot(topo, "results/exported_topo.dot", 25);
  return 0;
}
