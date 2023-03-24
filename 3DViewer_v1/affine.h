#ifndef AFFINE_H_
#define AFFINE_H_

#include <math.h>
#include <stdio.h>

/**
 @brief Move on X axis.
 @param vert_array - an array of vertexes.
 @param value - step value.
 @param vertexes_num - num of vertexes field i.e. num of iterations.
*/
void move_x(float** vert_array, float value, int vertexes_num);

/**
 @brief Move on Y axis.
 @param vert_array - an array of vertexes.
 @param value - step value.
 @param vertexes_num - num of vertexes field i.e. num of iterations.
*/
void move_y(float** vert_array, float value, int vertexes_num);

/**
 @brief Move on Z axis.
 @param vert_array - an array of vertexes.
 @param value - step value.
 @param vertexes_num - num of vertexes field i.e. num of iterations.
*/
void move_z(float** vert_array, float value, int vertexes_num);

void scale(float* vert_array, float scale, int vertexes_num);

/**
 @brief Transforms model over X axis.
 @param vert_array - an array of vertexes.
 @param value - value of the angle (transformed to RADs inside the function).
 @param vertexes_num - num of vertexes field i.e. num of iterations.
*/
void rotate_x(float** vert_array, float value, int vertexes_num);

/**
 @brief Transforms model over Y axis.
 @param vert_array - an array of vertexes.
 @param value - value of the angle (transformed to RADs inside the function).
 @param vertexes_num - num of vertexes field i.e. num of iterations.
*/
void rotate_y(float** vert_array, float value, int vertexes_num);

/**
 @brief Transforms model over Z axis.
 @param vert_array - an array of vertexes.
 @param value - value of the angle (transformed to RADs inside the function).
 @param vertexes_num - num of vertexes field i.e. num of iterations.
*/
void rotate_z(float** vert_array, float value, int vertexes_num);

/**
 @brief Stretch or squueze model on given coefficient.
 @param vert_array - an array of vertexes.
 @param scale - scaling coefficient.
 @param vertexes_num - num of vertexes field i.e. num of iterations.
*/
void scale_obj(float** vert_array, float scale, int vertexes_num);

#endif
