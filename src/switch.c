#include "switch.h"

#include <assert.h>
#include <math.h>

/**
 * initialize a switch object, given the line rate in microseconds
 */
struct switch_t *switch_init(double microsec_line_rate) {
  struct switch_t *ps = malloc(sizeof(struct switch_t));
  assert(ps != NULL);

  ps->last_dequeue_time = 0;
  ps->microsec_line_rate = microsec_line_rate;
  return ps;
}

/**
 * free the memory utilize by the switch object
 */
void switch_free(struct switch_t *ps) {
  assert(ps != NULL);
  free(ps);
}

/**
 * get the delay service time given lambda (average time between processing)
 */
static double service_delay(struct switch_t *s) {
  assert(s != NULL);

  assert(s->microsec_line_rate != 0);

  double lambda = 1.0 / s->microsec_line_rate;

  /* can actually be an issue due to floating point precision */
  assert(lambda != 0);

  double u = (double)rand() / (double)(RAND_MAX); // uniform from [0,1]
  double wait_time = -log(u) / lambda;
  return wait_time;
}

/**
 * get the delay time for the current switch, incorporating the service delay
 * and wait time
 */
double switch_get_delay(struct switch_t *s, double current_time,
                        double pkt_size) {
  double wait_time = 0.0;

  size_t i;
  for (i = 0; i < pkt_size * 8; i++) {
    wait_time += service_delay(s);
  }

  if (current_time >= s->last_dequeue_time) {
    s->last_dequeue_time = current_time + wait_time;
  } else {
    s->last_dequeue_time += wait_time;
  }
  return s->last_dequeue_time - current_time;
}
