#ifndef SWITCH_H
#define SWITCH_H

#include <stdint.h>
#include <stdlib.h>

struct switch_t {
  uint64_t last_dequeue_time;
  double microsec_line_rate;
};

/**
 * get the delay time for the current switch, incorporating the service delay
 * and wait time
 */
uint64_t switch_get_delay(struct switch_t *s, uint64_t current_time,
                          uint64_t pkt_size);

/**
 * initialize a switch object, given the line rate in microseconds
 */
struct switch_t *switch_init(double microsec_line_rate);

/**
 * free the memory utilize by the switch object
 */
void switch_free(struct switch_t *ps);

#endif /* SWITCH_H */
