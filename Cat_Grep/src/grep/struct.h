#ifndef  SRC_STRUCT_H
#define  SRC_STRUCT_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

typedef struct s_flags {
    int e;
    int i;
    int v;
    int c;
    int l;
    int n;
    int countArgument;
    char *key;
    char *pattern;
} t_flags ;

void s21_in_Struct(t_flags *countData);
int data_key(char *argv, t_flags *countData);
int data_pattern(char *argv, t_flags *countData);
int checking_key(t_flags *countData);
int checking_file(char *argv, t_flags *countData);
void string_selection(char *argv, t_flags *countData);
void output(char *choice_str, char *argv, t_flags *countData);
void free_data(t_flags *countData);

#endif // SRC_STRUCT_H