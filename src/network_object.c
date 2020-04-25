#include "network_object.h"

#include <assert.h>
#include <string.h>

struct network_object_t *network_object_init(const enum object_type_t type,
                                             const size_t id) {
  struct network_object_t *rtn = malloc(sizeof(struct network_object_t));
  assert(rtn != NULL);

  rtn->type = type;
  rtn->data = NULL;

  rtn->conn = NULL;
  rtn->n_conn = 0;

  rtn->id = id;

  memset(rtn->name, 0, OBJ_NAME_SIZE);
  strncpy(rtn->name, "UNNAMED", 7);

  return rtn;
}

void network_object_set_name(struct network_object_t *a, const char *name) {
  memset(a->name, 0, OBJ_NAME_SIZE);
  strncpy(a->name, name, OBJ_NAME_SIZE);
}

static void network_object_connect_one_side(struct network_object_t *a,
                                            struct network_object_t *b) {
  assert(a != NULL);
  assert(b != NULL);

  struct network_object_t **tmp =
      malloc(sizeof(struct network_object_t *) * (a->n_conn + 1));
  assert(tmp != NULL);

  if (a->conn != NULL) {
    memcpy(tmp, a->conn, sizeof(struct network_object_t *) * a->n_conn);
  }

  tmp[a->n_conn] = b;

  free(a->conn);
  a->conn = tmp;

  a->n_conn++;
}

void network_object_connect(struct network_object_t *a,
                            struct network_object_t *b) {
  network_object_connect_one_side(a, b);
  network_object_connect_one_side(b, a);
}

void network_object_free(struct network_object_t *a) {
  free(a->conn);
  free(a);
}
