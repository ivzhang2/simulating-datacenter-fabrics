#include "packet.h"
#include "simulation_runs.h"
#include "topology.h"

int main() {
  // struct topology_t *topo = topology_load("tests/test.topo", 15);
  // topology_export_to_dot(topo, "results/exported_topo.dot", 25);

  /*
    Hosts: h0, h1, h2, h3, h4, h5, h6
    Links: l0, l1, l2, l3
    Switches: s0, s1, s2, s3

    Path A: h0, l0, s0, l3, h2
    Path B: h1, l1, s2, l2, s3, h3
    Path C: h6, l0, s1, h4
    Path D: h0, l0, s0, h5

    Path A + B = disjoint (h0, l0, s0, l3, h2) + (h1, l1, s2, l2, s3, h3)

    Path A + C  = always intersect (h0, h6, l0, s0, s1, l3, h2, h4)

    Path A + D =  connected (h0, l0, s0, l3, h2, h5)

    Path A + B + C = (h0, h6, l0, s0, s1, l3, h2, h4) + (h1, l1, s2, l2, s3, h3)
    Path A + B + C + D = (h0, h6, l0, s0, s1, l3, h2, h4, h5) + (h1, l1, s2, l2,
    s3, h3)
  */

  /* initialziing servers */

  struct network_object_t *h0 = network_object_init(SERVER, 0);
  network_object_set_name(h0, "Host 0");
  struct network_object_t *h1 = network_object_init(SERVER, 1);
  network_object_set_name(h1, "Host 1");
  struct network_object_t *h2 = network_object_init(SERVER, 2);
  network_object_set_name(h2, "Host 2");
  struct network_object_t *h3 = network_object_init(SERVER, 3);
  network_object_set_name(h3, "Host 3");
  struct network_object_t *h4 = network_object_init(SERVER, 4);
  network_object_set_name(h4, "Host 4");
  struct network_object_t *h5 = network_object_init(SERVER, 5);
  network_object_set_name(h5, "Host 5");
  struct network_object_t *h6 = network_object_init(SERVER, 6);
  network_object_set_name(h6, "Host 6");

  /* initialziing links */
  struct network_object_t *l0 = network_object_init(LINK, 0);
  network_object_set_name(l0, "Link 0");
  struct network_object_t *l1 = network_object_init(LINK, 1);
  network_object_set_name(l1, "Link 1");
  struct network_object_t *l2 = network_object_init(LINK, 2);
  network_object_set_name(l2, "Link 2");
  struct network_object_t *l3 = network_object_init(LINK, 3);
  network_object_set_name(l3, "Link 3");

  /* initialziing switches */
  struct network_object_t *s0 = network_object_init(SWITCH, 0);
  network_object_set_name(s0, "Switch 0");
  struct network_object_t *s1 = network_object_init(SWITCH, 1);
  network_object_set_name(s1, "Switch 1");
  struct network_object_t *s2 = network_object_init(SWITCH, 2);
  network_object_set_name(s2, "Switch 2");
  struct network_object_t *s3 = network_object_init(SWITCH, 3);
  network_object_set_name(s3, "Switch 3");

  struct packet_t **packet_array = malloc(sizeof(struct packet_t *) * 4);

  /* Path A: h0, l0, s0, l3, h2 */
  struct packet_t *packet_a = malloc(sizeof(struct packet_t));
  packet_a->send_id = 0;
  packet_a->receive_id = 2;
  packet_a->n_path = 5;

  packet_a->path = malloc(sizeof(struct network_object_t *) * 5);
  packet_a->path[0] = h0;
  packet_a->path[1] = l0;
  packet_a->path[2] = s0;
  packet_a->path[3] = l3;
  packet_a->path[4] = h2;

  packet_array[0] = packet_a;

  /* Path B: h1, l1, s2, l2, s3, h3 */
  struct packet_t *packet_b = malloc(sizeof(struct packet_t));
  packet_b->send_id = 1;
  packet_b->receive_id = 3;
  packet_b->n_path = 6;

  packet_b->path = malloc(sizeof(struct network_object_t *) * 6);
  packet_b->path[0] = h1;
  packet_b->path[1] = l1;
  packet_b->path[2] = s2;
  packet_b->path[3] = l2;
  packet_b->path[4] = s3;
  packet_b->path[5] = h3;

  packet_array[1] = packet_b;

  /* Path C: h6, l0, s1, h4 */
  struct packet_t *packet_c = malloc(sizeof(struct packet_t));
  packet_c->send_id = 6;
  packet_c->receive_id = 4;
  packet_c->n_path = 4;

  packet_c->path = malloc(sizeof(struct network_object_t *) * 4);
  packet_c->path[0] = h6;
  packet_c->path[1] = l0;
  packet_c->path[2] = s1;
  packet_c->path[3] = h4;

  packet_array[2] = packet_c;

  /* Path D: h0, l0, s0, h5 */
  struct packet_t *packet_d = malloc(sizeof(struct packet_t));
  packet_d->send_id = 0;
  packet_d->receive_id = 5;
  packet_d->n_path = 4;

  packet_d->path = malloc(sizeof(struct network_object_t *) * 4);
  packet_d->path[0] = h0;
  packet_d->path[1] = l0;
  packet_d->path[2] = s0;
  packet_d->path[3] = h5;

  packet_array[3] = packet_d;

  /*
    Hosts: h0, h1, h2, h3, h4, h5, h6
    Links: l0, l1, l2, l3
    Switches: s0, s1, s2, s3

    Path A: h0, l0, s0, l3, h2
    Path B: h1, l1, s2, l2, s3, h3
    Path C: h6, l0, s1, h4
    Path D: h0, l0, s0, h5

    Path A + B = disjoint (h0, l0, s0, l3, h2) + (h1, l1, s2, l2, s3, h3)

    Path A + C  = always intersect (h0, h6, l0, s0, s1, l3, h2, h4)

    Path A + D =  connected (h0, l0, s0, l3, h2, h5)

    Path A + B + C = (h0, h6, l0, s0, s1, l3, h2, h4) + (h1, l1, s2, l2, s3, h3)
    Path A + B + C + D = (h0, h6, l0, s0, s1, l3, h2, h4, h5) + (h1, l1, s2, l2,
    s3, h3)
  */
  struct simulation_runs_t *simruns = generate_sim_runs(packet_array, 4);
  int DEBUG = 1;
  if (DEBUG) {
    struct topology_t **topo = simruns->topoarr;
    /*  total number has to be correct or else debug will seg fault */
    int total_topo = 2;
    for (int j = 0; j < total_topo; j++) {
      printf("\nprinting out TOPOLOGY #%d\n", j);
      printf("------------------------------------------\n");

      printf("\nprinting out SERVERS from topology #%d\n", j);
      printf("------------------------------------------\n");
      for (int i = 0; i < topo[j]->n_servers; i++) {
        printf("%s\n", topo[j]->servers[i]->name);
      }
      printf("\nprinting out LINKS from topology #%d\n", j);
      printf("------------------------------------------\n");
      for (int i = 0; i < topo[j]->n_links; i++) {
        printf("%s\n", topo[j]->links[i]->name);
      }
      printf("\nprinting out SWITCHES from topology  #%d\n", j);
      printf("------------------------------------------\n");
      for (int i = 0; i < topo[j]->n_switches; i++) {
        printf("%s\n", topo[j]->switches[i]->name);
      }
    }

    struct packet_t **packets = simruns->parr_arr;
    /* These 2 need to be correct in order for debug prints to work */
    int total_num_bundles = 2;      // total number of bundles
    int size_of_bundle[2] = {3, 1}; // size of bundle

    for (int j = 0; j < total_num_bundles; j++) {
      printf("\nprinting out BUNDLE #%d of SIZE #%d \n", j, size_of_bundle[j]);
      printf("------------------------------------------\n");

      printf("\nprinting out SEND ID and RECEIVE ID from packet bundle #%d of "
             "size #%d \n",
             j, size_of_bundle[j]);
      printf("------------------------------------------\n");
      for (int i = 0; i < size_of_bundle[j]; i++) {
        printf("send_id %zu, receive_id %zu\n", packets[j][i].send_id,
               packets[j][i].receive_id);
      }
    }
  }
  // simulation("tests/test_cdf.txt", 5.0, 100.0);

  return 0;
}
