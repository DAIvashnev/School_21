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
    int error_options;
    int stopPattern;
    int countArgument;
    char *key;
    char *pattern;
    char *file; 
    char *check_file;
    char *check_str;
} t_st ;

void s21_in_Struct(t_st *structData);
void parsingData(char *argv, t_st *structData);
void data_key(char *argv, t_st *structData);
void checking_key(t_st *structData);
void data_pattern(char *argv, t_st *structData);
void data_file(char *argv, t_st *structData);
void regexData(regex_t *re, int *error_regex, t_st *structData);
int checking_file(t_st *countData, int *countFile);
void search_matches(regex_t *re, regmatch_t *match, int *error_regex, t_st *structData);
int data_argv_e(char *argv, t_st *structData);
void output(t_st *structData);

void free_data(t_st *structData);

#endif // SRC_1HEADER_H