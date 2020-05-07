#include "common.h"
#include "simulation_runs.h"
#include "topology.h"
#include "trace.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>

static void route_benchmark_topology(struct trace_t *ptrace,
                                     struct topology_t *ptopo) {

  assert(ptrace != NULL);
  assert(ptopo != NULL);

  size_t path_length = 5;

  struct network_object_t **path_1 =
      malloc(sizeof(struct network_object_t *) * path_length);
  assert(path_1 != NULL);

  struct network_object_t **path_2 =
      malloc(sizeof(struct network_object_t *) * path_length);
  assert(path_2 != NULL);

  struct network_object_t **path_3 =
      malloc(sizeof(struct network_object_t *) * path_length);
  assert(path_3 != NULL);

  struct network_object_t **path_4 =
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

  path_3[0] = ptopo->servers[0];
  path_3[1] = ptopo->links[4];
  path_3[2] = ptopo->switches[2];
  path_3[3] = ptopo->links[5];
  path_3[4] = ptopo->servers[3];

  path_4[0] = ptopo->servers[0];
  path_4[1] = ptopo->links[6];
  path_4[2] = ptopo->switches[3];
  path_4[3] = ptopo->links[7];
  path_4[4] = ptopo->servers[4];

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
    } else if (ppkt->receive_id == 3) {
      ppkt->receive_id = ptopo->servers[3]->id;
      ppkt->path = path_3;
    } else if (ppkt->receive_id == 4) {
      ppkt->receive_id = ptopo->servers[4]->id;
      ppkt->path = path_4;
    } else {
      assert(0);
    }
  }
}

static void complete_flows(struct trace_t *ptrace, struct topology_t *ptopo) {
  assert(ptrace != NULL);
  assert(ptopo != NULL);

  struct packet_t *ppkt = packet_get_earliest(ptrace->pparr, ptrace->n_pparr);

  while (ppkt->state != PS_TERMINATED) {
    packet_traverse_next(ppkt);
    ppkt = packet_get_earliest(ptrace->pparr, ptrace->n_pparr);
  }
}

static void export_flow_times(struct trace_t *ptrace, const char *out_fname,
                              const size_t n_out_fname) {

  assert(ptrace != NULL);
  assert(out_fname != NULL);

  char *cpy_fname = strndup(out_fname, n_out_fname);

  FILE *pf = fopen(cpy_fname, "w");
  assert(pf != NULL);

  register size_t i;
  for (i = 0; i < ptrace->n_pparr; i++) {
    struct packet_t *ppkt = ptrace->pparr[i];
    fprintf(pf, "%zu,%zu,%zu,%lf,%lf\n", ppkt->flow_id, ppkt->send_id,
            ppkt->receive_id, ppkt->start_time, ppkt->curr_time);
  }

  fclose(pf);
  free(cpy_fname);
}

int main() {
  char *topo_fname = "tests/test.topo";
  struct topology_t *ptopo = topology_load(topo_fname, strlen(topo_fname));

  char *topo_dot_name = "results/test.topo.dot";
  topology_export_to_dot(ptopo, topo_dot_name, strlen(topo_dot_name));

  /* 10 Mbps switches */
  topology_init_switches(ptopo, MICROSEC_LINE_RATE);
  topology_init_links(ptopo, 2, 0.65);

  char *trace_fname = "results/generated_trace.csv.0";
  struct trace_t *ptrace = trace_load(trace_fname, strlen(trace_fname));

  printf("Loaded trace with %zu packets.\n", ptrace->n_pparr);

  route_benchmark_topology(ptrace, ptopo);

  complete_flows(ptrace, ptopo);

  char *result_fname = "results/fct.csv";
  export_flow_times(ptrace, result_fname, strlen(result_fname));

  struct simulation_runs_t *pruns = generate_sim_runs(ptrace);

  assert(pruns->n_tarr == 4);
  assert(pruns->n_topoarr == 4);

  simulation_runs_free(pruns);
  topology_free(ptopo);
  trace_free(ptrace);
}
