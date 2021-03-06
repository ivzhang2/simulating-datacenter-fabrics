#include "traffic_matrix.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>

/**
 * Initialize a traffic matrix object,
 * given the size (number of nodes)
 */
struct traffic_matrix_t *traffic_matrix_init(const size_t n_nodes) {
  struct traffic_matrix_t *pm = malloc(sizeof(struct traffic_matrix_t));
  assert(pm != NULL);

  assert(n_nodes > 0);
  pm->lst = malloc(sizeof(size_t) * n_nodes * n_nodes);
  assert(pm->lst != NULL);

  pm->n_nodes = n_nodes;

  pm->cumulative = false;
  pm->normalized = false;

  return pm;
}

/**
 * Free the memory utilize by the traffic matrix object
 */
void traffic_matrix_free(struct traffic_matrix_t *pm) {
  assert(pm != NULL);

  if (pm->lst != NULL) {
    free(pm->lst);
  }

  free(pm);
}

/**
 * Read the traffic from given file
 * and store the data in the initialized traffic matrix object
 */
struct traffic_matrix_t *traffic_matrix_from_file(const char *filename,
                                                  const size_t n_filename) {
  assert(filename != NULL);
  assert(n_filename > 0);

  FILE *pf;
  char *line = NULL;
  size_t len = 0;
  ssize_t read;

  char *cpy_filename = strndup(filename, n_filename);

  pf = fopen(cpy_filename, "r");
  assert(pf != NULL);

  struct traffic_matrix_t *pm = NULL;

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
        str_val = strtok(NULL, "\n");
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

/**
 * Normalized the values of the elements in the traffic matrix object
 */
static void traffic_matrix_normalize(struct traffic_matrix_t *pm) {
  assert(pm != NULL);
  assert(pm->lst != NULL);

  int i;

  double sum = 0;
  size_t len = pm->n_nodes * pm->n_nodes;

  for (i = 0; i < len; i++) {
    sum += pm->lst[i];
  }

  for (i = 0; i < len; i++) {
    pm->lst[i] = pm->lst[i] / sum;
  }

  pm->normalized = true;
}

/**
 * Summing up the values of the elements in the traffic matrix object
 */
static void traffic_matrix_accumulate(struct traffic_matrix_t *pm) {
  assert(pm != NULL);
  assert(pm->lst != NULL);

  int i;

  size_t len = pm->n_nodes * pm->n_nodes;

  double sum = 0;
  for (i = 0; i < len; i++) {
    sum += pm->lst[i];
    pm->lst[i] = sum;
  }

  pm->cumulative = true;
}

/**
 * Set the source and destination using random sampling for traffic simulation
 */
void traffic_matrix_sample(struct traffic_matrix_t *pm, size_t *src,
                           size_t *dst, unsigned int *pseed) {

  assert(pm != NULL);
  assert(pm->lst != NULL);
  assert(src != NULL);
  assert(dst != NULL);

  if (!pm->normalized) {
    traffic_matrix_normalize(pm);
  }

  if (!pm->cumulative) {
    traffic_matrix_accumulate(pm);
  }

  double y_sample = (double)rand_r(pseed) / (double)RAND_MAX;

  size_t index = 0;
  size_t len = pm->n_nodes * pm->n_nodes;

  while (pm->lst[index] <= y_sample && index < len) {
    index++;
  }

  *src = index / pm->n_nodes;
  *dst = index % pm->n_nodes;
}

// #define TRAFFIC_MATRIX_TEST

#ifdef TRAFFIC_MATRIX_TEST

/**
 * Testing - simulating the traffic using the matrix from file test.matrix,
 * simulation data simulation.csv and save the results in annotated.csv
 */
int main() {

  struct traffic_matrix_t *pm = traffic_matrix_from_file("test.matrix", 11);
  size_t src;
  size_t dst;

  FILE *pf;
  pf = fopen("../simulation.csv", "r");
  assert(pf != NULL);

  FILE *pout;
  pout = fopen("../annotated.csv", "w");
  assert(pout != NULL);

  char *line = NULL;
  size_t len = 0;
  ssize_t read;

  while ((read = getline(&line, &len, pf)) != -1) {
    traffic_matrix_sample(pm, &src, &dst);
    fprintf(pout, "%zu,%zu,%s", src, dst, line);
  }

  fclose(pf);
  if (line) {
    free(line);
  }

  fclose(pout);

  printf("Done\n");
}

#endif /* TRAFFIC_MATRIX_TEST */
