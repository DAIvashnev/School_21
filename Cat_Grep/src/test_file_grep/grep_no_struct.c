#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int data_key(char *argv, char **key, int *d_output);
int data_pattern(char *argv, char **pattern);
int checking_key(char *key);
int checking_file(char *argv);
void string_selection(char *pattern_str, char *argv, int *da_output);
void output(char *choice_str, char *argv, int **d_output);

int data_key(char *argv, char **key, int *d_output) {
    int flag = 0;
    if(argv[0] == '-') {
        *key = argv;
        *d_output -= 1;
        flag = 1;
    }
    return flag;
}

int data_pattern(char *argv, char **pattern) {
    int flag = 0;
    if(argv[0] != '-') {
        *pattern = argv;
        flag = 1;
    }
    return flag;
}

int checking_key(char *key) {
    int flag = 0;
    if(key[2] == 0 && key[0] != '0') {
        if(!(key[1] == 'i')) {
            printf("my_grep: invalid key - «%s»\n", key);
            flag = -1;
        }
    } else if(key[0] != '0') {
        printf("my_grep: invalid key - «%s»\n", key);
        flag = -1;
    }
    return flag;
}

int checking_file(char *argv) {
    FILE *fp;
    int flag = 0;
    int c;
    if((fp = fopen(argv, "r")) == NULL) {
        printf("my_grep: %s: There is no such file or directory\n", argv);
        flag = 1;
    } else if((c = getc(fp)) == EOF) {
        flag = 1;
        fclose(fp);
    } else {
        fclose(fp);
    }
    return flag;
}

void string_selection(char *pattern_str, char *argv, int *argc) {
    FILE *fp;
    char check_str[100];
    char *estr;
    fp = fopen(argv, "r");
    while(1) {
        estr = fgets(check_str, 100, fp);
        if(estr == NULL) {
            int c = strlen(check_str);
            if(strstr(check_str, pattern_str) != 0 && check_str[c] != '\n') {
                printf("\n");
            }
            break;
        } else if(strstr(check_str, pattern_str) != 0) {
            output(check_str, argv, &argc);
        }
    }
    fclose(fp);
}

void output(char *choice_str, char *argv, int **d_output) {
    if(**d_output > 3) {
        printf("%s:%s", argv, choice_str);
    } else {
        printf("%s", choice_str);
    }
}

int main(int argc, char *argv[]) {
    char *pattern;
    char *key = "0";
    int d_output = argc;
    for(size_t i = 1; argv[i] != NULL && data_key(argv[i], &key, &d_output) != 1; i++);
    for(size_t i = 1; argv[i] != NULL && data_pattern(argv[i], &pattern) != 1; i++);
    for(size_t i = 1; i != (size_t)argc && checking_key(key) == 0; i++) {
        if(strcmp(argv[i], key) != 0 && strcmp(argv[i], pattern) != 0 && checking_file(argv[i]) == 0) {
            string_selection(pattern, argv[i], &d_output);
        }
    }
    return 0;
}
