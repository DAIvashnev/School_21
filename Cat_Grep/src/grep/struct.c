#include "s21_grep.h"

void s21_in_Struct(t_st *structData) {
  structData->e = 0;
  structData->i = 0;
  structData->v = 0;
  structData->c = 0;
  structData->l = 0;
  structData->n = 0;
  structData->o = 0;
  structData->h = 0;
  structData->s = 0;
  structData->f = 0;
  structData->help_grep = 0;
  structData->error_options = 0;
  structData->error_f_file = 0;
  structData->empty_file = 0;
  structData->stopPattern = 0;
  structData->countArgument = 0;
  structData->countOutput = 0;
  structData->check_len = 0;
  structData->key = calloc(100, sizeof(char));
  structData->pattern = calloc(100, sizeof(char));
  structData->o_pattern = calloc(100, sizeof(char));
  structData->o_search = calloc(100, sizeof(char));
  structData->o_parsing = calloc(100, sizeof(char));
  structData->check_argv_f = calloc(100, sizeof(char));
  structData->file = calloc(100, sizeof(char));
  structData->check_file = calloc(100, sizeof(char));
  structData->check_str = calloc(1500, sizeof(char));
}

void free_data(t_st *structData) {
  free(structData->key);
  free(structData->pattern);
  free(structData->file);
  free(structData->check_file);
  free(structData->check_str);
  free(structData->o_pattern);
  free(structData->o_search);
  free(structData->check_argv_f);
  free(structData->o_parsing);
}
