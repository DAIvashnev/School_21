#ifndef  SRC_HEADER_H
#define  SRC_HEADER_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <regex.h>

typedef struct s_stData {
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
} t_stData ;

int data_argv_e(char *argv, t_flags *structData);
void s21_in_Struct(t_flags *structData);
int data_key(char *argv, t_flags *structData);
void checking_key(t_flags *structData);
int data_pattern(char *argv, t_flags *structData);
int data_argv_e(char *argv, t_flags *structData);
int checking_file(char *argv, t_flags *structData);
void regexData(t_flags *structData, regex_t *re, int *error_regex);
void string_selection(char *argv, t_flags *structData, regex_t *re, regmatch_t *match, int *error_regex);
void output_e(FILE *fp, char *argv, t_flags *structData, regex_t *re, regmatch_t *match, int *error_regex);
void output_v(FILE *fp, char *argv, t_flags *structData, regex_t *re, regmatch_t *match, int *error_regex);
void output_c(FILE *fp, char *argv, t_flags *structData, regex_t *re, regmatch_t *match, int *error_regex);
void output_l(FILE *fp, char *argv, t_flags *structData, regex_t *re, regmatch_t *match, int *error_regex);
void output_n(FILE *fp, char *argv, t_flags *structData, regex_t *re, regmatch_t *match, int *error_regex);
void output(char *argv, t_flags *structData);
void free_data(t_flags *structData);

#endif // SRC_HEADER_H