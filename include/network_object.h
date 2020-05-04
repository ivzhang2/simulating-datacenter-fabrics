#ifndef NETWORK_OBJECT_H
#define NETWORK_OBJECT_H

#include <stdlib.h>

enum object_type_t { SERVER, LINK, SWITCH };

#define OBJ_NAME_SIZE 255

struct network_object_t {
  enum object_type_t type;
  void *data;

  /* Objects this object is connected to */
  struct network_object_t **conn;
  size_t n_conn;

  size_t id;
  char name[OBJ_NAME_SIZE];
};

/**
* Initialize a network object, given the size and the type (switch/link/server)
*/
struct network_object_t *network_object_init(const enum object_type_t type,
                                             const size_t id);

/**
* Set a name for the network object
*/
void network_object_set_name(struct network_object_t *a, const char *name);

/**
* Given 2 network objects, added two-sided connections between the objects
*/
void network_object_connect(struct network_object_t *a,
                            struct network_object_t *b);

/**
* Free the memeory used by the network object
*/
void network_object_free(struct network_object_t *a);

#endif /* NETWORK_OBJECT_H */
