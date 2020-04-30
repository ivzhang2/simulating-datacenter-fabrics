#ifndef PACKET_H
#define PACKET_H

#include "network_object.h"

#include <stdint.h>
#include <stdlib.h>

/* Standard time to live length */
#define TTL_MAX 255

enum packet_state_t { PS_PENDING, PS_IN_NETWORK, PS_TERMINATED };

/* Network packet object */
struct packet_t {
  size_t send_id;    // ID of the sending host
  size_t receive_id; // ID of the receiving host

  uint64_t start_time; // start time of packet
  uint64_t curr_time;  // completion time of packet
  uint64_t size;       // size of packet in bytes

  /* time to live */
  size_t ttl;

  /* array of path objects */
  struct network_object_t **path;

  /* size of path array */
  size_t n_path;

  /* current position in path */
  size_t curr_pos;

  enum packet_state_t state;
};

void packet_traverse_next(struct packet_t *pp);

struct packet_t *packet_get_earliest(struct packet_t **const pparr,
                                     const size_t n_pparr);

#endif /* PACKET_H */
