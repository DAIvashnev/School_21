#include "struct.h"

void s21_in_Struct(t_flags *countData) {
    countData->e = 0;
    countData->i = 0;
    countData->v = 0;
    countData->c = 0;
    countData->l = 0;
    countData->n = 0;
    countData->countArgument = 0;
    countData->error_options = 0;
    countData->key = calloc(10, sizeof(char));
    countData->pattern = calloc(256, sizeof(char));
    countData->check_str = calloc(1000, sizeof(char));
}

void free_data(t_flags *countData) {
    free(countData->key);
    free(countData->pattern);
    free(countData->check_str);
}