#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int data_key(char *argv, char **key, int *pattern);
int checking_file(char *argv);
void string_selection(char *pattern_str, char *argv, int *argc, int *pattern);
int checking_string(char *pattern_str, char *choice_str);
void output(char *choice_str, char *argv, int **argc, int **pattern);

int data_key(char *argv, char **key, int *pattern) {
    int flag = 2;
    if(argv[0] == '-') {
        *key = argv;
        *pattern = 2;
        flag = 3;
    }
    return flag;
}

int checking_file(char *argv) {
    FILE *fp;
    int flag = 0;
    if((fp = fopen(argv, "r")) == NULL) {
        printf("my_grep: %s: There is no such file or directory\n", argv);
        flag = 1;
    } else {
        fclose(fp);
    }
    return flag;
}

void string_selection(char *pattern_str, char *argv, int *argc, int *pattern) {
    FILE *fp;
    int c;
    char *choice_str = NULL;
    int i = 0;
    fp = fopen(argv, "r");
    while((c = getc(fp)) != EOF) {
        choice_str = realloc(choice_str, (i + 1) * sizeof(char));
        choice_str[i] = c;
        i++;
        if(c == '\n') {
            choice_str[i] = '\0';
            if(checking_string(pattern_str, choice_str) == 1) {
                output(choice_str, argv, &argc, &pattern);
            }
            i = 0;
        }
    }
    choice_str[i] = '\n';
    choice_str[i+1] = '\0';
    if(checking_string(pattern_str, choice_str) == 1) {
        output(choice_str, argv, &argc, &pattern);
    }
    free(choice_str);
    fclose(fp);
}

int checking_string(char *pattern_str, char *choice_str) {
    size_t j = 0;
    int flag = 0;
    char *check_str = NULL;
    for(size_t i = 0; choice_str[i] != '\0'; i++) {
        if(choice_str[i] == pattern_str[j]) {
            check_str = realloc(check_str, (j + 1) * sizeof(char));
            check_str[j] = pattern_str[j];
            j++;
            if(strlen(pattern_str) == j && strcmp(pattern_str, check_str) == 0) {
                flag = 1;
            }
        } else {
            j = 0;
        }
    }
    free(check_str);

    return flag;
}

void output(char *choice_str, char *argv, int **argc, int **pattern) {
    if((**argc > 3 && **pattern == 1) || (**argc > 4 && **pattern == 2)) {
        printf("%s:%s", argv, choice_str);
    } else {
        printf("%s", choice_str);
    }
}

int main(int argc, char *argv[]) {
    int arguments = 0;
    int pattern = 1;
    char *key = "0";
    for(size_t i = 0; argv[i] != NULL && key[0] != '-'; i++) {
        arguments = data_key(argv[i], &key, &pattern);
    }
    for(; argv[arguments] != NULL; arguments++) {
        if(checking_file(argv[arguments]) == 0) {
            string_selection(argv[pattern], argv[arguments], &argc, &pattern);
        }
    }
    return 0;
}