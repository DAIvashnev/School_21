#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "affine.h"
#include "parser.h"

float cube_vertexes[] = {
    1.000000,  -1.000000, -1.000000, 1.000000,  -1.000000, 1.000000,
    -1.000000, -1.000000, 1.000000,  -1.000000, -1.000000, -1.000000,
    1.000000,  1.000000,  -0.999999, 0.999999,  1.000000,  1.000001,
    -1.000000, 1.000000,  1.000000,  -1.000000, 1.000000,  -1.000000,
};

float cube_vertexes_2[] = {
    1.000000,  -1.000000, -1.000000, 1.000000,  -1.000000, 1.000000,
    -1.000000, -1.000000, 1.000000,  -1.000000, -1.000000, -1.000000,
    1.000000,  1.000000,  -0.999999, 0.999999,  1.000000,  1.000001,
    -1.000000, 1.000000,  1.000000,  -1.000000, 1.000000,  -1.000000,
};

float cube_vertexes_3[] = {
    1.000000,  -1.000000, -1.000000, 1.000000,  -1.000000, 1.000000,
    -1.000000, -1.000000, 1.000000,  -1.000000, -1.000000, -1.000000,
    1.000000,  1.000000,  -0.999999, 0.999999,  1.000000,  1.000001,
    -1.000000, 1.000000,  1.000000,  -1.000000, 1.000000,  -1.000000,
};

float cube_vertexes_4[] = {
    1.000000,  -1.000000, -1.000000, 1.000000,  -1.000000, 1.000000,
    -1.000000, -1.000000, 1.000000,  -1.000000, -1.000000, -1.000000,
    1.000000,  1.000000,  -0.999999, 0.999999,  1.000000,  1.000001,
    -1.000000, 1.000000,  1.000000,  -1.000000, 1.000000,  -1.000000,
};

unsigned int cube_facets[] = {
    2, 3, 3, 4, 4, 2, 8, 7, 7, 6, 6, 8, 5, 6, 6, 2, 2, 5, 6, 7, 7, 3, 3, 6,
    3, 7, 7, 8, 8, 3, 1, 4, 4, 8, 8, 1, 1, 2, 2, 4, 4, 1, 5, 8, 8, 6, 6, 5,
    1, 5, 5, 2, 2, 1, 2, 6, 6, 3, 3, 2, 4, 3, 3, 8, 8, 4, 5, 1, 1, 8, 8, 5,
};

START_TEST(parser_indexes) {
  model model = {0};
  count_vs_and_fs("models/cube.obj", &model.vertexes_num, &model.facets_num);
  model.vert_array = calloc(sizeof(double), (model.vertexes_num * 3));
  model.poly_array = calloc(sizeof(unsigned int), ((model.facets_num + 1) * 2));
  fill_model("models/cube.obj", &model);

  for (int i = 0; i < ((int)model.facets_num + 1) * 2; i++) {
    ck_assert_float_eq(cube_facets[i] - 1, model.poly_array[i]);
  }
  free_model(&model);
}
END_TEST

START_TEST(parser_vertexes) {
  model model = {0};
  count_vs_and_fs("models/cube.obj", &model.vertexes_num, &model.facets_num);
  model.vert_array = calloc(sizeof(double), (model.vertexes_num * 3));
  model.poly_array = calloc(sizeof(unsigned int), ((model.facets_num + 1) * 2));
  fill_model("models/cube.obj", &model);

  for (int i = 0; i < model.vertexes_num * 3; i++) {
    ck_assert_float_eq(cube_vertexes[i], model.vert_array[i]);
  }
  free_model(&model);
}
END_TEST

START_TEST(affine_1) {
  model model = {0};
  count_vs_and_fs("models/cube.obj", &model.vertexes_num, &model.facets_num);
  model.vert_array = calloc(sizeof(double), (model.vertexes_num * 3));
  model.poly_array = calloc(sizeof(unsigned int), ((model.facets_num + 1) * 2));
  fill_model("models/cube.obj", &model);
  float angle = 45 * 3.14159265358979323846 / 180;

  for (int i = 0; i < model.vertexes_num; i++) {
    float y = cube_vertexes[i * 3 + 1];
    float z = cube_vertexes[i * 3 + 2];
    cube_vertexes[i * 3 + 1] = y * cos(angle) - z * sin(angle);
    cube_vertexes[i * 3 + 2] = y * sin(angle) + z * cos(angle);
  }

  rotate_x(&model.vert_array, 45, model.vertexes_num);

  for (int i = 0; i < model.vertexes_num; i++) {
    for (int j = 0; j < 3; j++) {
      ck_assert_float_eq(cube_vertexes[i * 3 + j], model.vert_array[i * 3 + j]);
    }
  }
  free_model(&model);
}
END_TEST

START_TEST(affine_2) {
  model model = {0};
  count_vs_and_fs("models/cube.obj", &model.vertexes_num, &model.facets_num);
  model.vert_array = calloc(sizeof(double), (model.vertexes_num * 3));
  model.poly_array = calloc(sizeof(unsigned int), ((model.facets_num + 1) * 2));
  fill_model("models/cube.obj", &model);
  float angle = 45 * 3.14159265358979323846 / 180;

  for (int i = 0; i < model.vertexes_num; i++) {
    float x = cube_vertexes_2[i * 3];
    float z = cube_vertexes_2[i * 3 + 2];
    cube_vertexes_2[i * 3] = x * cos(angle) + z * sin(angle);
    cube_vertexes_2[i * 3 + 2] = -x * sin(angle) + z * cos(angle);
  }

  rotate_y(&model.vert_array, 45, model.vertexes_num);

  for (int i = 0; i < model.vertexes_num; i++) {
    for (int j = 0; j < 3; j++) {
      ck_assert_float_eq(cube_vertexes_2[i * 3 + j],
                         model.vert_array[i * 3 + j]);
    }
  }
  free_model(&model);
}
END_TEST

START_TEST(affine_3) {
  model model = {0};
  count_vs_and_fs("models/cube.obj", &model.vertexes_num, &model.facets_num);
  model.vert_array = calloc(sizeof(double), (model.vertexes_num * 3));
  model.poly_array = calloc(sizeof(unsigned int), ((model.facets_num + 1) * 2));
  fill_model("models/cube.obj", &model);
  float angle = 45 * 3.14159265358979323846 / 180;

  for (int i = 0; i < model.vertexes_num; i++) {
    float x = cube_vertexes_3[i * 3];
    float y = cube_vertexes_3[i * 3 + 1];
    cube_vertexes_3[i * 3] = x * cos(angle) - y * sin(angle);
    cube_vertexes_3[i * 3 + 1] = x * sin(angle) + y * cos(angle);
  }

  rotate_z(&model.vert_array, 45, model.vertexes_num);

  for (int i = 0; i < model.vertexes_num; i++) {
    for (int j = 0; j < 3; j++) {
      ck_assert_float_eq(cube_vertexes_3[i * 3 + j],
                         model.vert_array[i * 3 + j]);
    }
  }
  free_model(&model);
}
END_TEST

START_TEST(move_xyz) {
  model model = {0};
  count_vs_and_fs("models/cube.obj", &model.vertexes_num, &model.facets_num);
  model.vert_array = calloc(sizeof(double), (model.vertexes_num * 3));
  model.poly_array = calloc(sizeof(unsigned int), ((model.facets_num + 1) * 2));
  fill_model("models/cube.obj", &model);

  float value = 5;
  for (int i = 0; i < model.vertexes_num; i++) {
    cube_vertexes_4[i * 3] += value;
  }

  move_x(&model.vert_array, value, model.vertexes_num);

  for (int i = 0; i < model.vertexes_num; i++) {
    for (int j = 0; j < 3; j++) {
      ck_assert_float_eq(cube_vertexes_4[i * 3 + j],
                         model.vert_array[i * 3 + j]);
    }
  }

  for (int i = 0; i < model.vertexes_num; i++) {
    cube_vertexes_4[i * 3 + 1] += value;
  }

  move_y(&model.vert_array, value, model.vertexes_num);

  for (int i = 0; i < model.vertexes_num; i++) {
    for (int j = 0; j < 3; j++) {
      ck_assert_float_eq(cube_vertexes_4[i * 3 + j],
                         model.vert_array[i * 3 + j]);
    }
  }

  for (int i = 0; i < model.vertexes_num; i++) {
    cube_vertexes_4[i * 3 + 2] += value;
  }

  move_z(&model.vert_array, value, model.vertexes_num);

  for (int i = 0; i < model.vertexes_num; i++) {
    for (int j = 0; j < 3; j++) {
      ck_assert_float_eq(cube_vertexes_4[i * 3 + j],
                         model.vert_array[i * 3 + j]);
    }
  }
  free_model(&model);
}
END_TEST
int main(void) {
  Suite *s1 = suite_create("Parser");
  TCase *tc1_1 = tcase_create("parser_test");
  TCase *tc1_2 = tcase_create("parser_indexes");
  Suite *s2 = suite_create("Affine transformations");
  TCase *tc2_1 = tcase_create("Affine_1");
  TCase *tc2_2 = tcase_create("Affine_2");
  TCase *tc2_3 = tcase_create("Affine_3");
  TCase *tc2_4 = tcase_create("Move_xyz");
  SRunner *sr = srunner_create(s1);
  int nf;

  suite_add_tcase(s1, tc1_1);
  tcase_add_test(tc1_1, parser_vertexes);
  suite_add_tcase(s1, tc1_2);
  tcase_add_test(tc1_2, parser_indexes);

  suite_add_tcase(s2, tc2_1);
  suite_add_tcase(s2, tc2_2);
  suite_add_tcase(s2, tc2_3);
  suite_add_tcase(s2, tc2_4);

  tcase_add_test(tc2_1, affine_1);
  tcase_add_test(tc2_2, affine_2);
  tcase_add_test(tc2_3, affine_3);
  tcase_add_test(tc2_3, move_xyz);

  srunner_add_suite(sr, s2);

  srunner_set_fork_status(sr, CK_NOFORK);

  srunner_run_all(sr, CK_ENV);
  nf = srunner_ntests_failed(sr);
  srunner_free(sr);

  return nf == 0 ? 0 : 1;
}
