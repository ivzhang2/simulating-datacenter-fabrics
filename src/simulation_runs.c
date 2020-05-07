#include "simulation_runs.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>

void simulation_runs_free(struct simulation_runs_t *ps) {
  free(ps->tarr);

  register size_t i;
  for (i = 0; i < ps->n_topoarr; i++) {
    free(ps->topoarr[i]);
  }

  free(ps);
}

static int is_same_network_object(struct network_object_t *a,
                                  struct network_object_t *b) {
  enum object_type_t a_type = a->type;
  enum object_type_t b_type = b->type;
  size_t a_id = a->id;
  size_t b_id = b->id;
  if (a_type == b_type && a_id == b_id) {
    return 1;
  }
  return 0;
}

static int is_in_topology(struct network_object_t *a, struct topology_t *topo) {
  enum object_type_t type = a->type;

  if (type == SWITCH) {
    for (int i = 0; i < topo->n_switches; i++) {
      if (is_same_network_object(a, topo->switches[i])) {
        return 1;
      }
    }
  } else if (type == LINK) {
    for (int i = 0; i < topo->n_links; i++) {
      if (is_same_network_object(a, topo->links[i])) {
        return 1;
      }
    }
  }

  return 0;
}

static struct topology_t *create_new_topology(struct network_object_t **path,
                                              size_t n_path) {
  struct topology_t *topo = malloc(sizeof(struct topology_t));

  topo->n_links = 0;
  topo->n_switches = 0;
  topo->n_servers = 0;
  topo->links = malloc(sizeof(struct network_object_t *));
  topo->switches = malloc(sizeof(struct network_object_t *));
  topo->servers = malloc(sizeof(struct network_object_t *));

  for (int i = 0; i < n_path; i++) {
    enum object_type_t type = path[i]->type;
    if (type == LINK) {
      if (topo->n_links == 0) {
        topo->links[0] = path[i];
      } else {
        topo->links = realloc(topo->links, sizeof(struct network_object_t *) *
                                               (topo->n_links + 1));
        topo->links[topo->n_links] = path[i];
      }
      topo->n_links += 1;
    } else if (type == SWITCH) {
      if (topo->n_switches == 0) {
        topo->switches[0] = path[i];
      } else {
        topo->switches =
            realloc(topo->switches,
                    sizeof(struct network_object_t *) * (topo->n_switches + 1));
        topo->switches[topo->n_switches] = path[i];
      }
      topo->n_switches += 1;
    } else {
      if (topo->n_servers == 0) {
        topo->servers[0] = path[i];
      } else {
        topo->servers =
            realloc(topo->servers,
                    sizeof(struct network_object_t *) * (topo->n_servers + 1));
        topo->servers[topo->n_servers] = path[i];
      }
      topo->n_servers += 1;
    }
  }

  return topo;
}

static struct topology_t *union_topology(struct topology_t *topo,
                                         struct network_object_t **path,
                                         size_t n_path) {
  struct topology_t *temp = malloc(sizeof(struct topology_t));
  temp->n_links = topo->n_links;
  temp->n_switches = topo->n_switches;
  temp->n_servers = topo->n_servers;
  temp->links = topo->links;
  temp->switches = topo->switches;
  temp->servers = topo->servers;

  for (int i = 0; i < n_path; i++) {
    enum object_type_t type = path[i]->type;
    if (type == LINK) {
      int inTopo = is_in_topology(path[i], topo);
      if (!inTopo) {
        temp->links = realloc(temp->links, sizeof(struct network_object_t *) *
                                               (temp->n_links + 1));
        temp->links[temp->n_links] = path[i];
        temp->n_links += 1;
      }

    } else if (type == SWITCH) {
      int inTopo = is_in_topology(path[i], topo);
      if (!inTopo) {
        temp->switches =
            realloc(temp->switches,
                    sizeof(struct network_object_t *) * (temp->n_switches + 1));
        temp->switches[temp->n_switches] = path[i];
        temp->n_switches += 1;
      }
    } else {
      int inTopo = is_in_topology(path[i], topo);
      if (!inTopo) {
        temp->servers =
            realloc(temp->servers,
                    sizeof(struct network_object_t *) * (temp->n_servers + 1));
        temp->servers[temp->n_servers] = path[i];
        temp->n_servers += 1;
      }
    }
  }

  free(topo);
  return temp;
}

/* Logic:

        For each packet,
                For each topology
                        If its in the topology, union the path and the topology
                        Else, create a new topology and new packet_arr

        (I.E. Loop through the routes of the current packet and if a route
   matches, union the who PATH Else make new topology)
*/

struct simulation_runs_t *generate_sim_runs(struct trace_t *in_tarr) {
  struct packet_t **p_arr = in_tarr->pparr;
  size_t num_packets = in_tarr->n_pparr;

  struct simulation_runs_t *sim_runs = malloc(sizeof(struct simulation_runs_t));
  assert(sim_runs != NULL);

  struct trace_t *tarr = malloc(sizeof(struct trace_t));
  assert(tarr != NULL);

  struct topology_t **topo_arr = malloc(sizeof(struct topology_t));
  assert(topo_arr != NULL);

  size_t num_topology = 0; // number of topologies stored in arrays

  // 1 if path was merge, else 0 to create new topology and packet array
  int match;

  register size_t i;
  register size_t j;
  register size_t k;

  for (i = 0; i < num_packets; ++i) {

    match = 0;

    for (j = 0; j < num_topology; j++) {
      if (match) {
        break;
      }
      for (k = 0; k < p_arr[i]->n_path; k++) {
        if (is_in_topology(p_arr[i]->path[k], topo_arr[j])) {
          topo_arr[j] =
              union_topology(topo_arr[j], p_arr[i]->path, p_arr[i]->n_path);
          match = 1;
          tarr[j].pparr = realloc(tarr[j].pparr, sizeof(struct packet_t *) *
                                                     (tarr[j].n_pparr + 1));
          tarr[j].pparr[tarr[j].n_pparr] = p_arr[i];
          tarr[j].n_pparr += 1;
          break;
        }
      }
    }

    if (!match) {
      tarr = realloc(tarr, sizeof(struct trace_t) * (num_topology + 1));

      topo_arr =
          realloc(topo_arr, sizeof(struct topology_t *) * (num_topology + 1));

      tarr[num_topology].pparr = malloc(sizeof(struct packet_t *));
      tarr[num_topology].pparr[0] = p_arr[i];

      tarr[num_topology].n_pparr = 1;

      topo_arr[num_topology] =
          create_new_topology(p_arr[i]->path, p_arr[i]->n_path);

      num_topology += 1;
    }
  }

  sim_runs->tarr = tarr;
  sim_runs->topoarr = topo_arr;

  sim_runs->n_topoarr = num_topology;
  sim_runs->n_tarr = num_topology;

  return sim_runs;
}
