#include "trace.h"

#include "common.h"
#define _GNU_SOURCE
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void trace_free(struct trace_t *pt) {
  free(pt->pparr);
  free(pt);
}

struct trace_t *trace_load(const char *filename, const size_t n_filename) {
  FILE *pf;
  char *line = NULL;
  size_t len = 0;
  ssize_t read;

  char *cpy_filename = strndup(filename, n_filename);

  struct trace_t *pt = malloc(sizeof(struct trace_t));
  assert(pt != NULL);

  pt->pparr = NULL;

  pf = fopen(cpy_filename, "r");
  assert(pf != NULL);

  size_t n_pkt = 0;
  double abs_arrival = 0.0;

  while ((read = getline(&line, &len, pf)) != -1) {
    struct packet_t *pp = packet_init();
    assert(pp != NULL);

    if (pt->pparr == NULL) {
      pt->pparr = malloc(sizeof(struct packet_t *));
    } else {
      pt->pparr = realloc(pt->pparr, sizeof(struct packet_t *) * (n_pkt + 1));
    }

    assert(pt->pparr != NULL);

    pt->pparr[n_pkt] = pp;
    ++n_pkt;

    char *token = strtok(line, ",");
    assert(token != NULL);

    pp->send_id = atol(token);

    token = strtok(NULL, ",");
    assert(token != NULL);

    pp->receive_id = atol(token);

    token = strtok(NULL, ",");
    assert(token != NULL);

    abs_arrival += atof(token);

    pp->start_time = abs_arrival;
    pp->curr_time = abs_arrival;

    token = strtok(NULL, "\n");

    double flow_size = atof(token);
    double curr_size = flow_size > MTU ? MTU : flow_size;
    double curr_time = pp->start_time;

    pp->size = curr_size;
    flow_size -= curr_size;

    while (flow_size > 0) {
      pt->pparr = realloc(pt->pparr, sizeof(struct packet_t *) * (n_pkt + 1));

      struct packet_t *pp_more = malloc(sizeof(struct packet_t));
      assert(pp_more != NULL);

      pt->pparr[n_pkt] = pp_more;
      ++n_pkt;

      pp_more->send_id = pp->send_id;
      pp_more->receive_id = pp->receive_id;

      curr_time += (MTU * 8.0) / (MICROSEC_LINE_RATE);

      pp_more->start_time = curr_time;
      pp_more->curr_time = curr_time;

      curr_size = flow_size > MTU ? MTU : flow_size;

      pp_more->size = curr_size;
      flow_size -= curr_size;
    }
  }

  fclose(pf);

  if (line) {
    free(line);
  }

  free(cpy_filename);

  pt->n_pparr = n_pkt;
  return pt;
}
