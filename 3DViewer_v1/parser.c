#include "parser.h"

void free_model(model* model) {
  model->facets_num = 0;
  model->vertexes_num = 0;
  model->max_min.max_x = 0;
  model->max_min.max_y = 0;
  model->max_min.max_z = 0;
  model->max_min.min_x = 0;
  model->max_min.min_y = 0;
  model->max_min.min_z = 0;
  if (model->vert_array) {
    free(model->vert_array);
    model->vert_array = NULL;
  }
  if (model->poly_array) {
    free(model->poly_array);
    model->poly_array = NULL;
  }
}

int header_is_ok(char* line, char* line_header) {
  int status = 1;
  if ((line[0] == 'v' || line[0] == 'f') && line[1] == WSPACE) {
    *line_header = line[0];
  } else
    status = 0;
  return status;
}

int header_is_v(char line_header) { return (line_header == 'v') ? 1 : 0; }

int header_is_f(char line_header) { return (line_header == 'f') ? 1 : 0; }

void count_vertexes(char* line, int* vertexes) {
  if (line[0] == 'f') {
    for (int i = 2; i < (int)strlen(line); i++) {
      if (line[i] == WSPACE || line[i] == LINEFEED) {
        *vertexes += 1;
      }
    }
  }
}

int count_vs_and_fs(char* filepath, int* vertex_num, unsigned int* facets_num) {
  FILE* file = fopen(filepath, "r");
  int status = OK;
  if (file != NULL) {
    char* line = NULL;
    size_t buffsize = 0;
    char line_header = 0;
    while (getline(&line, &buffsize, file) != -1) {
      if (header_is_ok(line, &line_header)) {
        if (header_is_v(line_header)) {
          *vertex_num += 1;
        } else if (header_is_f(line_header)) {
          int vertexes = 0;
          count_vertexes(line, &vertexes);
          *facets_num += vertexes;
        }
      }
    }
    if (line) free(line);
  } else
    status = ERROR;
  if (file) {
    fclose(file);
  } else
    printf("Corrupted File\n");
  return status;
}

int isdigit_or_dot_or_sign(char c) {
  return (isdigit(c) || c == '.' || c == '-') ? 1 : 0;
}

void parse_vertex_values(char* line, unsigned int* poly_array,
                         unsigned int* j) {
  int read_flag = 1;
  unsigned int number = 0;
  int num_of_vertexes = 0;
  int i = 0;
  while (line[i] == 'f' || line[i] == WSPACE) i++;
  for (; i < (int)strlen(line); i++) {
    if (isdigit(line[i]) && read_flag) {
      number *= 10;
      number += line[i] - '0';
    } else {
      if (read_flag) {
        if (num_of_vertexes == 0) {
          poly_array[*j] = number - 1;
          *j += 1;
        } else {
          poly_array[*j] = number - 1;
          *j += 1;
          poly_array[*j] = number - 1;
          *j += 1;
        }
        number = 0;
        read_flag = 0;
        num_of_vertexes++;
      }
      if (line[i] == WSPACE) {
        if (line[i + 1] != NEWLINE) read_flag = 1;
      }
    }
  }
  poly_array[*j] =
      poly_array[*j - ((num_of_vertexes * 2) - 1)];  //[ 5, 1, 1, 4, 4, 5 ]
  *j += 1;
}

void parse_xyz(char* line, float* x, float* y, float* z) {
  int counter = 0;
  char value_in_str[64] = {0};
  char* nullptr = NULL;
  int i = 0;
  while (line[i] == 'v' || line[i] == WSPACE) i++;
  for (int j = 0; i < (int)strlen(line); i++) {
    if (isdigit_or_dot_or_sign(line[i])) {
      value_in_str[j] = line[i];
      j++;
    } else if (line[i] == WSPACE || line[i] == LINEFEED) {
      value_in_str[j] = '\0';
      if (counter == 0)
        *x = strtod(value_in_str, &nullptr);
      else if (counter == 1)
        *y = strtod(value_in_str, &nullptr);
      else if (counter == 2)
        *z = strtod(value_in_str, &nullptr);
      counter++;
      j = 0;
    }
  }
}

bool approx_equal(float a, float b) {
  return fabs(a - b) <= ((fabs(a) < fabs(b) ? fabs(b) : fabs(a)) * PRECISION);
}

bool def_greater(float a, float b) {
  return (a - b) > ((fabs(a) < fabs(b) ? fabs(b) : fabs(a)) * PRECISION);
}

bool def_less(float a, float b) {
  return (b - a) > ((fabs(a) < fabs(b) ? fabs(b) : fabs(a)) * PRECISION);
}

int compare_float(float a, float b) {
  int status = 0;
  if (approx_equal(a, b))
    ;
  else {
    if (def_greater(a, b))
      status = 1;
    else if (def_less(a, b))
      status = -1;
  }
  return status;
}

void upd_maxmin(model* model, float x, float y, float z) {
  if (compare_float(x, model->max_min.max_x) == 1) {
    model->max_min.max_x = x;
  } else if (compare_float(x, model->max_min.min_x) == -1) {
    model->max_min.min_x = x;
  }
  if (compare_float(y, model->max_min.max_y) == 1) {
    model->max_min.max_y = y;
  } else if (compare_float(y, model->max_min.min_y) == -1) {
    model->max_min.min_y = y;
  }
  if (compare_float(z, model->max_min.max_z) == 1) {
    model->max_min.max_z = z;
  } else if (compare_float(z, model->max_min.min_z) == -1) {
    model->max_min.min_z = z;
  }
}

void write_vertexes(char* line, model* model, int* i) {
  float x = 0;
  float y = 0;
  float z = 0;
  parse_xyz(line, &x, &y, &z);
  upd_maxmin(model, x, y, z);
  model->vert_array[*i] = x;
  *i += 1;
  model->vert_array[*i] = y;
  *i += 1;
  model->vert_array[*i] = z;
  *i += 1;
}

void fill_model(char* filepath, model* model) {
  FILE* file = fopen(filepath, "r");
  char* line = NULL;
  size_t buffsize = 0;
  char line_header = 0;
  int i = 0;
  unsigned int j = 0;
  while (getline(&line, &buffsize, file) != -1) {  // doesn't work on Windows
    if (header_is_ok(line, &line_header)) {
      if (header_is_v(line_header)) {
        write_vertexes(line, model, &i);
      } else if (header_is_f(line_header)) {
        parse_vertex_values(line, model->poly_array, &j);
      }
    }
  }
  free(line);
  fclose(file);
}

float max_3_point(float x, float y, float z) {
  float res = (compare_float(x, y) == 1) ? x : y;
  return res = (compare_float(res, z)) ? res : z;
}

int load_model(char* filepath, model* model) {
  model->vertexes_num = 0;
  model->facets_num = 0;
  int res = count_vs_and_fs(filepath, &model->vertexes_num, &model->facets_num);
  if (res == OK) {
    if ((model->vert_array =
             calloc(sizeof(float), (model->vertexes_num * 3)))) {
      if ((model->poly_array =
               calloc(sizeof(unsigned int), ((model->facets_num + 1) * 2)))) {
        fill_model(filepath, model);

        max_min_t a = model->max_min;

        float centrX = a.min_x + (a.max_x - a.min_x) / 2;
        float centrY = a.min_y + (a.max_y - a.min_y) /
                                     2;  // Calculate median coords of xyz
        float centrZ = a.min_z + (a.max_z - a.min_z) / 2;

        move_x(&model->vert_array, -centrX, model->vertexes_num);
        move_y(&model->vert_array, -centrY, model->vertexes_num);
        move_z(&model->vert_array, -centrZ, model->vertexes_num);

        float d_max = max_3_point(a.max_x - a.min_x, a.max_y - a.min_y,
                                  a.max_z - a.min_z);

        float sc_v = (0.3 - (0.3 * (-1.))) / d_max;

        scale_obj(&model->vert_array, sc_v, model->vertexes_num);
      }
    }
  }
  return res;
}
