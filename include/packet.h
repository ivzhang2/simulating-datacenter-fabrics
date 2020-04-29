#ifndef PACKET_H
#define PACKET_H

#include <stdlib.h>

/* Standard time to live length */
#define TTL_MAX 255

/* Network packet object */
struct packet_t {
  size_t send_id;    // ID of the sending host
  size_t receive_id; // ID of the receiving host

  double start_time; // start time of packet
  double wait_time;  // wait time of packet
  double size;       // size of packet in bytes

  /* time to live */
  size_t ttl;

  /* array of path objects */
  network_object_t **path;

  /* size of path array */
  size_t n_path;
};

#endif /* PACKET_H */
