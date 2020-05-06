#include "common.h"
#include "topology.h"
#include "trace.h"

#include <stdio.h>
#include <string.h>

int main() {
  char *topo_fname = "tests/test.topo";
  struct topology_t *ptopo = topology_load(topo_fname, strlen(topo_fname));

  /* 10 Mbps switches */
  topology_init_switches(ptopo, MICROSEC_LINE_RATE);
  topology_init_links(ptopo, 2, 0.65);

  char *trace_fname = "results/generated_trace.csv.0";

  struct trace_t *ptrace = trace_load(trace_fname, strlen(trace_fname));

  printf("Loaded trace with %zu packets.\n", ptrace->n_pparr);
}
