#ifndef  SRC_STRUCT_H
#define  SRC_STRUCT_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <regex.h>

typedef struct s_flags {
    int e;
    int i;
    int v;
    int c;
    int l;
    int n;
    int countArgument;
    int error_options;
    char *key;
    char *pattern;
    char *check_str;
} t_flags ;

int data_argv_e(char *argv, t_flags *countData);
void s21_in_Struct(t_flags *countData);
int data_key(char *argv, t_flags *countData);
void checking_key(t_flags *countData);
int data_pattern(char *argv, t_flags *countData);
int data_argv_e(char *argv, t_flags *countData);
int checking_file(char *argv, t_flags *countData);
void regexData(t_flags *countData, regex_t *re, int *error_regex);
void string_selection(char *argv, t_flags *countData, regex_t *re, regmatch_t *match, int *error_regex);
void output_e(FILE *fp, char *argv, t_flags *countData, regex_t *re, regmatch_t *match, int *error_regex);
void output_v(FILE *fp, char *argv, t_flags *countData, regex_t *re, regmatch_t *match, int *error_regex);
void output_c(FILE *fp, char *argv, t_flags *countData, regex_t *re, regmatch_t *match, int *error_regex);
void output_l(FILE *fp, char *argv, t_flags *countData, regex_t *re, regmatch_t *match, int *error_regex);
void output_n(FILE *fp, char *argv, t_flags *countData, regex_t *re, regmatch_t *match, int *error_regex);
void output(char *argv, t_flags *countData);
void free_data(t_flags *countData);

#endif // SRC_STRUCT_H