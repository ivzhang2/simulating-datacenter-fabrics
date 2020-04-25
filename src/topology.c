#include "topology.h"

#include <stdio.h>
#include <assert.h>

struct topology_t* topology_load(const char* filename, const size_t n_filename) {
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

  int row = 0;

  while ((read = getline(&line, &len, pf)) != -1) {
    if (pm == NULL) {
      size_t n_nodes = atol(strtok(line, "\n"));
      pm = traffic_matrix_init(n_nodes);
      continue;
    }

    int i;
    char *str_val;

    for (i = 0; i < pm->n_nodes; i++) {
      if (i == 0) {
        str_val = strtok(line, ",");
      } else if (i == pm->n_nodes - 1) {
        str_val = strtok(line, "\n");
      } else {
        str_val = strtok(NULL, ",");
      }

      assert(str_val != NULL);

      pm->lst[row * pm->n_nodes + i] = atof(str_val);
      assert(pm->lst[row * pm->n_nodes + i] >= 0);
    }

    ++row;
  }

  if (pm != NULL) {
    assert(row == pm->n_nodes);
  }

  fclose(pf);
  if (line) {
    free(line);
  }

  free(cpy_filename);

  return pm;

}
