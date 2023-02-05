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
  structData->countSTR = 0;
  structData->countOutput = 0;
  structData->check_len = 0;
  structData->key = NULL;
  structData->pattern = NULL;
  structData->file = NULL;
  structData->check_argv_f = NULL;
  structData->o_pattern = NULL;
  structData->check_file = NULL;
  structData->o_search = NULL;
  structData->o_parsing = NULL;
  structData->check_str = NULL;
}

void free_data(t_st *structData) {
  free(structData->key);
  free(structData->pattern);
  free(structData->file);
  free(structData->check_file);
  free(structData->o_pattern);
  free(structData->check_argv_f);
  free(structData->o_parsing);
}
