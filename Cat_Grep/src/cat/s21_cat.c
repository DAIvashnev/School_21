#include "s21_cat.h"

int data_key(char *argv, char **key) {
  int flag = 0;
  if (argv[0] == '-') {
    *key = argv;
    flag = 1;
  }
  return flag;
}

void checking_gnu_key(char **key) {
  char *b = "--number-nonblank";
  char *v = "--show-nonprinting";
  char *E = "--show-ends";
  char *n = "--number";
  char *s = "--squeeze-blank";
  char *T = "--show-tabs";
  if (strcmp(*key, b) == 0) {
    *key = "-b\0";
  }
  if (strcmp(*key, v) == 0) {
    *key = "-v\0";
  }
  if (strcmp(*key, E) == 0) {
    *key = "-E\0";
  }
  if (strcmp(*key, n) == 0) {
    *key = "-n\0";
  }
  if (strcmp(*key, s) == 0) {
    *key = "-s\0";
  }
  if (strcmp(*key, T) == 0) {
    *key = "-T\0";
  }
}

int checking_key(char *key) {
  int flag = 0;
  if (key[2] == 0 && key[0] != '0') {
    if (!(key[1] == 'b' || key[1] == 'n' || key[1] == 's' || key[1] == 'e' ||
          key[1] == 'E' || key[1] == 'v' || key[1] == 't' || key[1] == 'T')) {
      printf("my_cat: invalid key - «%s»\n", key);
      flag = 1;
    }
  } else if (key[0] != '0') {
    printf("my_cat: invalid key - «%s»\n", key);
    flag = 1;
  }
  return flag;
}

int checking_file(char *argv) {
  int flag = 0;
  FILE *ch;
  if ((ch = fopen(argv, "r")) == NULL) {
    printf("my_cat: %s: There is no such file or directory\n", argv);
    flag = 1;
  } else {
    fclose(ch);
  }

  return flag;
}

void show_nonprinting(int *c, FILE *fp, const char *key) {
  while ((*c = getc(fp)) != EOF) {
    if (key[1] == 'e' && *c == '\n') {
      printf("$");
    }
    if (key[1] == 't' && *c == '\t') {
      *c = 73;
      printf("^");
    }
    if ((*c < 33 && *c != 9 && *c != 10 && *c != 13 && *c != 32) || *c == 127) {
      printf("^");
      if (*c + 64 < 128) {
        printf("%c", *c += 64);
      } else {
        *c = 128 - 127 + 62;
        printf("%c", *c);
      }

    } else {
      putc(*c, stdout);
    }
  }
  fclose(fp);
}

void output_b(int *c, FILE *fp) {
  int num = 0;
  int check = 0;
  while ((*c = getc(fp)) != EOF) {
    if (*c != '\n' && check == 0) {
      check = 1;
      num += 1;
      printf("%6d\t", num);
    }
    putc(*c, stdout);
    if (*c == '\n') {
      check = 0;
    }
  }
  fclose(fp);
}

void output_n(int *c, FILE *fp) {
  int num = 0;
  int ch_c = 10;
  while ((*c = getc(fp)) != EOF) {
    if (ch_c == '\n') {
      num += 1;
      printf("%6d\t", num);
    }
    putc(*c, stdout);
    ch_c = *c;
  }
  fclose(fp);
}

void output_s(int *c, FILE *fp) {
  int f = 1;
  while ((*c = getc(fp)) != EOF) {
    if (*c == '\n') {
      f++;
    } else {
      f = 0;
    }
    if (f <= 2) {
      putc(*c, stdout);
    }
  }
  fclose(fp);
}

void output_E(int *c, FILE *fp) {
  while ((*c = getc(fp)) != EOF) {
    if (*c == '\n') {
      printf("$");
    }
    putc(*c, stdout);
  }
  fclose(fp);
}

void output_T(int *c, FILE *fp) {
  while ((*c = getc(fp)) != EOF) {
    if (*c == '\t') {
      *c = 73;
      printf("^");
    }
    putc(*c, stdout);
  }
  fclose(fp);
}

void output(char *argv, char *key) {
  FILE *fp;
  int c;
  fp = fopen(argv, "r");
  if (key[1] == 'b') {
    output_b(&c, fp);
  } else if (key[1] == 'n') {
    output_n(&c, fp);
  } else if (key[1] == 's') {
    output_s(&c, fp);
  } else if (key[1] == 'E') {
    output_E(&c, fp);
  } else if (key[1] == 'T') {
    output_T(&c, fp);
  } else if (key[1] == 'e' || key[1] == 'v' || key[1] == 't') {
    show_nonprinting(&c, fp, key);
  } else {
    while ((c = getc(fp)) != EOF) {
      putc(c, stdout);
    }
    fclose(fp);
  }
}

int main(int argc, char *argv[]) {
  int result_key;
  char *key = "0";
  result_key = data_key(argv[1], &key);
  checking_gnu_key(&key);
  if (result_key == 1) {
    for (size_t i = 2; i != (size_t)argc && checking_key(key) != 1; i++) {
      if (checking_file(argv[i]) != 1) {
        output(argv[i], key);
      }
    }
  } else {
    for (size_t i = 1; i != (size_t)argc; i++) {
      if (checking_file(argv[i]) != 1) {
        output(argv[i], key);
      }
    }
  }
  return 0;
}
