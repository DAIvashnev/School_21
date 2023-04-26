#ifndef PARSER_H_
#define PARSER_H_

#define _GNU_SOURCE

#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "affine.h"

#define WSPACE 32
#define SLASH 47
#define NEWLINE 13
#define LINEFEED 10
#define PRECISION 1E-10

/* ---
PARSER USAGE
 - Create model with: model model = {0};
 - Load .obj file into model with load model function.
 - Free space with free_model function.
*/

typedef struct max_min {
  float max_x;
  float max_y;
  float max_z;
  float min_x;
  float min_y;
  float min_z;
} max_min_t;

typedef struct model {
  float* vert_array;
  unsigned int* poly_array;
  max_min_t max_min;
  int vertexes_num;
  unsigned int facets_num;
} model;

enum { OK, ERROR };

/**
 @brief Loads 3D Model from .obj file into model struct.
 @param filepath - str as a path to the .obj file.
 @param model - pointer to a model to store vertexes and facets.
 @return 1/0 OK/ERROR CODE
*/
int load_model(char* filepath, model* model);

/**
 @brief Counts number of vertexes and facets fields in .obj file.
 @param filepath - str as a path to the .obj file.
 @param vertex_num - pointer to the field in the model struct.
 @param facets_num - pointer to the field in the model struct.
 @return 1/0 OK/ERROR CODE
*/
int count_vs_and_fs(char* filepath, int* vertex_num, unsigned int* facets_num);

/**
 @brief Fills model struct inners.
 @param filepath - str as a path to the .obj file.
 @param model - pointer to the model struct object.
*/
void fill_model(char* filepath, model* model);

/**
 @brief Frees model struct inners.
 @param model - pointer to the model struct object.
*/
void free_model(model* model);

#endif
