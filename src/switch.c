#include "switch.h"

#include <assert.h>
#include <math.h>

struct switch_t *switch_init(double microsec_line_rate) {
  struct switch_t *ps = malloc(sizeof(struct switch_t));
  assert(ps != NULL);

  ps->last_dequeue_time = 0;
  ps->microsec_line_rate = microsec_line_rate;
  return ps;
}

void switch_free(struct switch_t *ps) {
  assert(ps != NULL);
  free(ps);
}

// get the delay time given lambda (average time between processing)
static uint64_t service_delay(struct switch_t *s) {
  assert(s != NULL);

  assert(s->microsec_line_rate != 0);

  double lambda = 1.0 / s->microsec_line_rate;

  /* can actually be an issue due to floating point precision */
  assert(lambda != 0);

  double u = (double)rand() / (double)(RAND_MAX); // uniform from [0,1]
  double wait_time = -log(u) / lambda;
  return (uint64_t)wait_time;
}

uint64_t switch_get_delay(struct switch_t *s, uint64_t current_time) {
  uint64_t wait_time = service_delay(s);

  if (current_time >= s->last_dequeue_time) {
    s->last_dequeue_time = current_time + wait_time;
  } else {
    s->last_dequeue_time += wait_time;
  }
  return s->last_dequeue_time - current_time;
}
