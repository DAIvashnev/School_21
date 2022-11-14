#ifndef  SRC_S21_CAT_HEADER_H
#define  SRC_S21_CAT_HEADER_H
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int data_key(char *argv, char **key);
void checking_gnu_key(char **key);
int checking_file(char *argv);
int checking_key(char *key);
void show_nonprinting(int *c, FILE * fp, const char *key);
void output_b(int *c, FILE *fp);
void output_n(int *c, FILE *fp);
void output_s(int *c, FILE *fp);
void output_E(int *c, FILE *fp);
void output_T(int *c, FILE *fp);
void output(char *argv, char *key);

#endif // SRC_S21_CAT_HEADER_H