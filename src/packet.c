#include "packet.h"

#include "link.h"
#include "switch.h"

#include <assert.h>

/**
* get the next incoming packet, store its data and evaluate the incoming time (considering all the delays)
*/
void packet_traverse_next(struct packet_t *pp) {

  if (pp->state == PS_TERMINATED) {
    return;
  }

  if (pp->state == PS_PENDING) {
    pp->state = PS_IN_NETWORK;
  }

  struct network_object_t *obj = pp->path[pp->curr_pos];
  assert(obj != NULL);

  if (obj->type == SWITCH) {
    struct switch_t *ps = (struct switch_t *)obj->data;
    pp->curr_time += switch_get_delay(ps, pp->curr_time);
  }

  if (obj->type == LINK) {
    struct link_t *pl = (struct link_t *)obj->data;
    pp->curr_time += pl->calculated_delay;
  }

  ++pp->curr_pos;
  --pp->ttl;

  if ((pp->curr_pos == pp->n_path) || (pp->ttl == 0)) {
    pp->state = PS_TERMINATED;
  }
}

/**
* Given the list of the incoming packets, get the next one (earliest) in line
*/
struct packet_t *packet_get_earliest(struct packet_t **const pparr,
                                     const size_t n_pparr) {
  assert(n_pparr > 0);

  struct packet_t *pp = pparr[0];

  register size_t i;

  for (i = 1; i < n_pparr; i++) {
    if ((pp->curr_time > pparr[i]->curr_time) && (pp->state != PS_TERMINATED)) {
      pp = pparr[i];
    }
  }

  return pp;
}
