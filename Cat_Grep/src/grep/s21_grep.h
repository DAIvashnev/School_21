#ifndef SRC_S21_GREP_H
#define SRC_S21_GREP_H
#include <ctype.h>
#include <errno.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

typedef struct s_st {
  int e;
  int i;
  int v;
  int c;
  int l;
  int n;
  int o;
  int h;
  int s;
  int f;
  int help_grep;
  int error_options;
  int error_f_file;
  int empty_file;
  int stopPattern;
  int countArgument;
  int countSTR;
  int countOutput;
  int check_len;
  char *key;
  char *pattern;
  char *o_pattern;
  char *o_search;
  char *o_parsing;
  char *check_argv_f;
  char *file;
  char *check_file;
  char *check_str;
} t_st;

void s21_grep_help(const char *argv, t_st *structData);
void s21_in_Struct(t_st *structData);
void parsingData(char *argv, t_st *structData);
void data_key(char *argv, t_st *structData);
void checking_key(t_st *structData);
void data_pattern(char *argv, t_st *structData);
void data_file(char *argv, t_st *structData);
void s21_regComp(regex_t *re, int *error_regex, t_st *structData);
int checking_file(t_st *countData, int *countFile, int *check_s);
void search_matches(regex_t *re, regmatch_t *match, int *error_regex,
                    t_st *structData);
void output_v(FILE *fp, t_st *structData, regex_t *re, regmatch_t *match,
              int *error_regex);
void output_c(FILE *fp, t_st *structData, regex_t *re, regmatch_t *match,
              int *error_regex);
void output_l(FILE *fp, t_st *structData, regex_t *re, regmatch_t *match,
              int *error_regex);
void output_n(FILE *fp, t_st *structData, regex_t *re, regmatch_t *match,
              int *error_regex);
void output_o(FILE *fp, t_st *structData, regex_t *re, regmatch_t *match,
              int *error_regex);
void o_parsing(t_st *structData, const int *count);
void data_argv_e(const char *argv, t_st *structData);
void data_argv_f(const char *argv, t_st *structData);
void output(t_st *structData);
void count_output(t_st *structData);
void free_data(t_st *structData);

#endif  // SRC_S21_GREP_H