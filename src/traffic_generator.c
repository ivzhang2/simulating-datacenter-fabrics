#include "arrival.h"
#include "flow.h"

#include <assert.h>
#include <stdlib.h>
#include <time.h>

/*
   Given: filename of the CDF, interarrival time between flows, and the
   total simulation time (milliseconds) Returns large csv ("simulation.csv")
   with interarrival times
*/
static void generate_traffic(char *filename, char *output_fname,
                             double interarrival_time,
                             double total_simulation_time) {
  FILE *fp;
  fp = fopen(output_fname, "w+");
  assert(fp != NULL);

  double seed = rand();
  double lambda = total_simulation_time / interarrival_time;

  // set the seed from the top of the simulation to be used for all functions
  // downstreeam (not attaching it poissonprocess arrival time only)
  srand(seed);

  struct flow_node_t *data_flows = init_flow(filename);

  double next_arrival;
  double next_data_flow;

  while (total_simulation_time > 0) {
    // no longer need to initialize a poissonprocess object,
    // we can pass in the lambda and call the function get_arrival_time directly
    next_arrival = get_arrival_time(lambda);

    next_data_flow = get_next_flow(data_flows);
    total_simulation_time -= next_arrival;

    fprintf(
        fp, "%lf,%lf \n", next_arrival,
        next_data_flow); // write to csv in format "arrival time, data size \n"
  }

  fclose(fp);
}

int main() {
  generate_traffic("tests/test_cdf.txt", "results/simulation.csv", 1.0, 1000.0);
}
