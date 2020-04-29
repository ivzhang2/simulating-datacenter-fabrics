#include "packet.h"

#include "link.h"
#include "switch.h"

#include <assert.h>

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
}
