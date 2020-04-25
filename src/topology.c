#include "topology.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>

struct topology_t *topology_load(const char *filename,
                                 const size_t n_filename) {
  assert(filename != NULL);
  assert(n_filename > 0);

  FILE *pf;
  char *line = NULL;
  size_t len = 0;
  ssize_t read;

  char *cpy_filename = strndup(filename, n_filename);

  pf = fopen(filename, "r");
  assert(pf != NULL);

  struct topology_t *topo = malloc(sizeof(struct topology_t));
  assert(topo != NULL);

  topo->switches = NULL;
  topo->links = NULL;
  topo->servers = NULL;

  size_t id = 0;

  while ((read = getline(&line, &len, pf)) != -1) {
    char *str_val;

    str_val = strtok(line, " ");

    if (strncpy("switches", str_val, 8) == 0) {
      str_val = strtok(line, "\n");
      topo->n_switches = atol(str_val);
      assert(topo->n_switches > 0);

      topo->switches =
          malloc(sizeof(struct network_object_t *) * topo->n_switches);
      assert(topo->switches != NULL);

      size_t i;
      for (i = 0; i < topo->n_switches; i++) {
        topo->switches[i] = network_object_init(SWITCH, id);

        char name[255];
        sprintf(name, "s%zu", i);

        network_object_set_name(topo->switches[i], name);
        ++id;
      }

      continue;
    }

    if (strncpy("servers", str_val, 7) == 0) {
      str_val = strtok(line, "\n");
      topo->n_servers = atol(str_val);
      assert(topo->n_servers > 0);

      topo->servers =
          malloc(sizeof(struct network_object_t *) * topo->n_servers);
      assert(topo->servers != NULL);

      size_t i;
      for (i = 0; i < topo->n_servers; i++) {
        topo->servers[i] = network_object_init(SERVER, id);

        char name[255];
        sprintf(name, "h%zu", i);

        network_object_set_name(topo->servers[i], name);
        ++id;
      }

      continue;
    }

    if (strncpy("links", str_val, 5) == 0) {
      str_val = strtok(line, "\n");
      topo->n_links = atol(str_val);
      assert(topo->n_links > 0);

      topo->links = malloc(sizeof(struct network_object_t *) * topo->n_links);
      assert(topo->links != NULL);

      size_t i;
      for (i = 0; i < topo->n_links; i++) {
        topo->links[i] = network_object_init(LINK, id);

        char name[255];
        sprintf(name, "l%zu", i);

        network_object_set_name(topo->links[i], name);
        ++id;
      }

      continue;
    }

    if (strncpy("connect", str_val, 7) == 0) {
      struct network_object_t *a;
      struct network_object_t *b;

      str_val = strtok(line, " ");
      assert(strnlen(str_val, 10) > 1);

      char type = str_val[0];
      assert(type == 'l');

      str_val++;
      size_t index_a = atol(str_val);
      assert(index_a < topo->n_links);

      a = topo->links[index_a];

      str_val = strtok(line, "\n");
      assert(strnlen(str_val, 10) > 1);

      type = str_val[0];
      assert(type == 's' || type == 'h');

      str_val++;
      size_t index_b = atol(str_val);

      if (type == 's') {
        assert(index_b < topo->n_switches);

        b = topo->switches[index_b];
      }

      if (type == 'h') {
        assert(index_b < topo->n_servers);
        b = topo->servers[index_b];
      }

      network_object_connect(a, b);
    }
  }

  fclose(pf);
  if (line) {
    free(line);
  }

  free(cpy_filename);

  return topo;
}
