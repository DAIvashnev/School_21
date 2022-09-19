#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void func_one(void);
void func_two(void);
void func_three(void);

char input[500];
char output[500];
char inp_two[500];
int n;
int f = 0;
FILE *fp;

int main() {
  while (n != -1) {
    if (scanf("%d", &n) != 0) {
      switch (n) {
      case 1:
        func_one();
        break;
      case 2:
        func_two();
        break;
      case 3:
        func_three();
        break;
      default:
        if (n != -1) {
          fseek(stdin, 0, SEEK_END);
          printf("n/a\n");
        }
        break;
      }
    } else {
      printf("n/a\n");
      fseek(stdin, 0, SEEK_END);
    }
  }
  return 0;
}

void func_one(void) {
  scanf("%s", input);
  fp = fopen(input, "r");
  if (fp == NULL) {
    printf("n/a\n");
    f = 1;
  } else {
    while (fgets(output, 500, fp)) {
      printf("%s", output);
    }
    if ((output == NULL || output[0] == '\0') && f == 0) {
      printf("n/a\n");
    } else {
      printf("\n");
    }
  }
  output[0] = '\0';
  f = 0;
}

void func_two(void) {
  fseek(stdin, 0, SEEK_END);
  fgets(inp_two, 500, stdin);
  char *p = strchr(inp_two, '\n');
  *p = '\0';
  fp = fopen(input, "r");
  if (fp == NULL) {
    printf("n/a\n");
  } else {
    fclose(fp);
    fp = fopen(input, "a");
    fputs(inp_two, fp);
    fclose(fp);
    fp = fopen(input, "r");
    while (fgets(output, 500, fp)) {
      printf("%s", output);
    }
    if ((output == NULL || output[0] == '\0') && f == 0) {
      printf("n/a\n");
    } else {
      printf("\n");
    }
    fclose(fp);
  }
}

void func_three(void) {

}