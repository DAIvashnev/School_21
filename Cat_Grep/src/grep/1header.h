#ifndef  SRC_1HEADER_H
#define  SRC_1HEADER_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <regex.h>

typedef struct s_st{
    int e;
    int i;
    int v;
    int c;
    int l;
    int n;
    int help_grep;
    int error_options;
    int stopPattern;
    int countArgument;
    int countOutput;
    int check_len;
    char *key;
    char *pattern;
    char *file; 
    char *check_file;
    char *check_str;
} t_st ;

void s21_grep_help(t_st *structData);
void s21_in_Struct(t_st *structData);
void parsingData(char *argv, t_st *structData);
void data_key(char *argv, t_st *structData);
void checking_key(t_st *structData);
void data_pattern(char *argv, t_st *structData);
void data_file(char *argv, t_st *structData);
void s21_regComp(regex_t *re, int *error_regex, t_st *structData);
int checking_file(t_st *countData, int *countFile);
void search_matches(regex_t *re, regmatch_t *match, int *error_regex, t_st *structData);
void output_v(FILE *fp, t_st *structData, regex_t *re, regmatch_t *match, int *error_regex);
void output_c(FILE *fp, t_st *structData, regex_t *re, regmatch_t *match, int *error_regex);
void output_l(FILE *fp, t_st *structData, regex_t *re, regmatch_t *match, int *error_regex);
void output_n(FILE *fp, t_st *structData, regex_t *re, regmatch_t *match, int *error_regex);
int data_argv_e(char *argv, t_st *structData);
void output(t_st *structData);
void count_output(t_st *structData);
void free_data(t_st *structData);

#endif // SRC_1HEADER_H