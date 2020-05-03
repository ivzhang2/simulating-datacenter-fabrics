#include "arrival.h"
#include "flow.h"
#include "traffic_matrix.h"

#include <assert.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>

#define MAX_FILENAME 1024

struct _thread_args_t {
  char *cdf_file;
  char *tm_file;
  char *output_file;

  size_t n_cdf_file;
  size_t n_tm_file;
  size_t n_output_file;

  double ia_time;
  double sim_time;
};

static pthread_mutex_t lock;

static void *_threaded_traffic_gen(void *args) {
  struct _thread_args_t *unpacked = (struct _thread_args_t *)args;

  FILE *pout = fopen(unpacked->output_file, "w+");
  assert(pout != NULL);

  pthread_mutex_lock(&lock);

  struct traffic_matrix_t *pm =
      traffic_matrix_from_file(unpacked->tm_file, unpacked->n_tm_file);

  struct flow_node_t *data_flows = init_flow(unpacked->cdf_file);

  pthread_mutex_unlock(&lock);

  while (unpacked->sim_time > 0) {
    double next_arrival = get_arrival_time(unpacked->ia_time);
    double next_data_flow = get_next_flow(data_flows);

    size_t src;
    size_t dst;

    traffic_matrix_sample(pm, &src, &dst);
    unpacked->sim_time -= next_arrival;

    /* src,dst,arrival time, data size */
    fprintf(pout, "%zu,%zu,%lf,%lf \n", src, dst, next_arrival, next_data_flow);
  }

  fclose(pout);

  return NULL;
}

/*
   Given: filename of the CDF, interarrival time between flows, and the
   total simulation time (milliseconds) Returns large csv ("simulation.csv")
   with interarrival times
*/
static void generate_traffic(char *cdf_file, char *tm_file, char *output_file,
                             double interarrival_time,
                             double total_simulation_time, size_t n_threads) {
  double seed = 42;

  // set the seed from the top of the simulation to be used for all functions
  // downstreeam (not attaching it poissonprocess arrival time only)
  srand(seed);

  pthread_t *threads = malloc(sizeof(pthread_t) * n_threads);
  struct _thread_args_t *targs =
      malloc(sizeof(struct _thread_args_t) * n_threads);
  assert(threads != NULL);

  int rtn = pthread_mutex_init(&lock, NULL);
  assert(rtn == 0);

  register size_t i;
  for (i = 0; i < n_threads; i++) {
    targs[i].sim_time = total_simulation_time / n_threads;
    targs[i].ia_time = interarrival_time;

    targs[i].cdf_file = strndup(cdf_file, MAX_FILENAME);
    targs[i].n_cdf_file = strnlen(targs[i].cdf_file, MAX_FILENAME);

    targs[i].tm_file = strndup(tm_file, MAX_FILENAME);
    targs[i].n_tm_file = strnlen(targs[i].tm_file, MAX_FILENAME);

    targs[i].output_file = strndup(output_file, MAX_FILENAME);

    size_t n_output = strnlen(output_file, MAX_FILENAME) + 15;
    targs[i].output_file = malloc(n_output);
    memset(targs[i].output_file, '\0', n_output);

    snprintf(targs[i].output_file, n_output, "%s.%zu", output_file, i);

    targs[i].n_output_file = strnlen(targs[i].output_file, MAX_FILENAME);

    rtn = pthread_create(&threads[i], NULL, &_threaded_traffic_gen,
                         (void *)&targs[i]);
  }

  for (i = 0; i < n_threads; i++) {
    pthread_join(threads[i], NULL);
  }

  pthread_mutex_destroy(&lock);

  for (i = 0; i < n_threads; i++) {
    free(targs[i].cdf_file);
    free(targs[i].tm_file);
    free(targs[i].output_file);
  }

  free(targs);
  free(threads);
}

int main() {
  generate_traffic("tests/test_cdf.txt", "tests/test.matrix",
                   "results/generated_trace.csv", 1.0, 100000.0, 1);
}
