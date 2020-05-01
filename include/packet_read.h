#ifndef PACKET_READ_H
#define PACKET_READ_H

# include "packet.h"

#include <stdio.h>
#include <string.h>

// Read all packets from file
struct packet_t** packet_read(char *filename);

#endif /* PACKET_READ_H */