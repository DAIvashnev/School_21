#include "1header.h"

void s21_in_Struct(t_st *structData) {
    structData->e = 0;
    structData->i = 0;
    structData->v = 0;
    structData->c = 0;
    structData->l = 0;
    structData->n = 0;
    structData->countArgument = 0;
    structData->error_options = 0;
    structData->key = calloc(10, sizeof(char));
    structData->pattern = calloc(256, sizeof(char));
    structData->file = calloc(1000, sizeof(char));
    structData->check_str = calloc(1000, sizeof(char));
}

void free_data(t_st *structData) {
    free(structData->key);
    free(structData->pattern);
    free(structData->file);
    free(structData->check_str);
}