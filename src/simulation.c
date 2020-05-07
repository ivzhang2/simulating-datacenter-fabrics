#include "common.h"
#include "simulation_runs.h"
#include "topology.h"
#include "trace.h"

#include <stdio.h>
#include <string.h>

static void route_benchmark_topology(struct trace_t *ptrace,
                                     struct topology_t *ptopo) {

  size_t path_length = 5;

  struct network_object_t **path_1 =
      malloc(sizeof(struct network_object_t *) * path_length);

  struct network_object_t **path_2 =
      malloc(sizeof(struct network_object_t *) * path_length);

  path_1[0] = ptopo->servers[0];
  path_1[1] = ptopo->links[0];
  path_1[2] = ptopo->switches[0];
  path_1[3] = ptopo->links[1];
  path_1[4] = ptopo->servers[1];

  path_2[0] = ptopo->servers[0];
  path_2[1] = ptopo->links[2];
  path_2[2] = ptopo->switches[1];
  path_2[3] = ptopo->links[3];
  path_2[4] = ptopo->servers[2];

  register size_t i;

  for (i = 0; i < ptrace->n_pparr; i++) {
    struct packet_t *ppkt = ptrace->pparr[i];

    ppkt->send_id = ptopo->servers[0]->id;
    ppkt->n_path = path_length;

    if (ppkt->receive_id == 1) {
      ppkt->receive_id = ptopo->servers[1]->id;
      ppkt->path = path_1;
    } else if (ppkt->receive_id == 2) {
      ppkt->receive_id = ptopo->servers[2]->id;
      ppkt->path = path_2;
    } else {
      assert(0);
    }
  }
}

int main() {
  char *topo_fname = "tests/test.topo";
  struct topology_t *ptopo = topology_load(topo_fname, strlen(topo_fname));

  /* 10 Mbps switches */
  topology_init_switches(ptopo, MICROSEC_LINE_RATE);
  topology_init_links(ptopo, 2, 0.65);

  char *trace_fname = "results/generated_trace.csv.0";

  struct trace_t *ptrace = trace_load(trace_fname, strlen(trace_fname));

  printf("Loaded trace with %zu packets.\n", ptrace->n_pparr);

  route_benchmark_topology(ptrace, ptopo);

  struct simulation_runs_t *pruns = generate_sim_runs(ptrace);

  assert(pruns->n_tarr == 2);
  assert(pruns->n_topoarr == 2);

  simulation_runs_free(pruns);
  topology_free(ptopo);
  trace_free(ptrace);
}
