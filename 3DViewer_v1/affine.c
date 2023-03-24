#include "affine.h"

// [0.5, 0.6, 0.4, 0.8 ...]
// matrix[i][j]

void move_x(float** vert_array, float value, int vertexes_num) {
  for (int i = 0; i < vertexes_num; i++) {
    (*vert_array)[i * 3] += value;
  }
}

void move_y(float** vert_array, float value, int vertexes_num) {
  for (int i = 0; i < vertexes_num; i++) {
    (*vert_array)[i * 3 + 1] += value;
  }
}

void move_z(float** vert_array, float value, int vertexes_num) {
  for (int i = 0; i < vertexes_num; i++) {
    (*vert_array)[i * 3 + 2] += value;
  }
}

void scale_obj(float** vert_array, float scale, int vertexes_num) {
  for (int i = 0; i < vertexes_num; i++) {
    for (int j = 0; j < 3; j++) {
      if (scale > 1e-07) (*vert_array)[i * 3 + j] *= scale;
    }
  }
}

void rotate_x(float** vert_array, float value, int vertexes_num) {
  value = value * 3.14159265358979323846 / 180;
  for (int i = 0; i < vertexes_num; i++) {
    // for(int j = 0; j < 3; j++) {
    float y = (*vert_array)[i * 3 + 1];
    float z = (*vert_array)[i * 3 + 2];
    (*vert_array)[i * 3 + 1] = y * cos(value) - z * sin(value);
    (*vert_array)[i * 3 + 2] = y * sin(value) + z * cos(value);
    //}
  }
}

void rotate_y(float** vert_array, float value, int vertexes_num) {
  value = value * 3.14159265358979323846 / 180;
  for (int i = 0; i < vertexes_num; i++) {
    // for(int j = 0; j < 3; j++) {
    float x = (*vert_array)[i * 3];
    float z = (*vert_array)[i * 3 + 2];
    (*vert_array)[i * 3] = x * cos(value) + z * sin(value);
    (*vert_array)[i * 3 + 2] = -x * sin(value) + z * cos(value);
    //}
  }
}

void rotate_z(float** vert_array, float value, int vertexes_num) {
  value = value * 3.14159265358979323846 / 180;
  for (int i = 0; i < vertexes_num; i++) {
    // for(int j = 0; j < 3; j++) {
    float x = (*vert_array)[i * 3];
    float y = (*vert_array)[i * 3 + 1];
    (*vert_array)[i * 3] = x * cos(value) - y * sin(value);
    (*vert_array)[i * 3 + 1] = x * sin(value) + y * cos(value);
    //}
  }
}
