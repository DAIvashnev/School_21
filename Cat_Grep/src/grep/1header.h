#ifndef  SRC_1HEADER_H
#define  SRC_HEADER_H
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
    int countArgument;
    int error_options;
    char *key;
    char *pattern;
    char *file; 
    char *check_str;
} t_st ;

void s21_in_Struct(t_st *structData);
void parsingData(char *argv, t_st *structData);
void data_key(char *argv, t_st *structData);
void checking_key(t_st *structData);
void data_pattern(char *argv, t_st *structData);

void free_data(t_st *structData);

#endif // SRC_HEADER_H