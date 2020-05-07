#ifndef SIMULATION_RUNS_H
#define SIMULATION_RUNS_H

#include <stdio.h>
#include <string.h>

#include "packet.h"
#include "topology.h"
#include "trace.h"

struct simulation_runs_t {
  struct trace_t *tarr; // 2D array of pointers to traces

  // pointer to array of topologies based on packet movement
  struct topology_t **topoarr;

  size_t n_tarr;
  size_t n_topoarr;
};

/*
        Function: generate_sim_runs

        @discussion
        generates an object containing the isolated/pruned network structure

        @params
        packet_t** p_arr: pointer to an array of pointers to packets
        size_t num_packets: number of packets passed

        @returns
        struct simulation_runs_t*: a simulation_runs object of isolated
   topologies where parr_arr[i] is an array of packets corresponding to
   topoarr[i]
*/

struct simulation_runs_t *generate_sim_runs(struct trace_t *in_tarr);

/* Note that this assumes you have an original copy of the loaded topology and
 * trace which you are freeing. So it doesn't free the objects pointed to by the
 * trace and topology arrays */
void simulation_runs_free(struct simulation_runs_t *ps);

#endif /* SIMULATION_RUNS_H */
