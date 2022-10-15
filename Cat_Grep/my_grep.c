#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int cheking_file(char *argv);
void string_selection(const char *str, char *argv, int *argc);
void check_search(const char *str, char *ch_str, int **argc, char *argv);
void output(char *str, int ***argc, char *argv);

int cheking_file(char *argv) {
    FILE *ch;
    int flag = 0;
    if((ch = fopen(argv, "r")) == NULL) {
        printf("my_grep: %s: There is no such file or directory\n", argv);
        flag = 1;
    }
    return flag;
}


void string_selection(const char *str, char *argv, int *argc) {
    FILE *ch;
    int c;
    char *ch_str = NULL;
    int i = 0;
    ch = fopen(argv, "r");
    while((c = getc(ch)) != EOF) {
        ch_str = realloc(ch_str, (i + 1) * sizeof(char));
        ch_str[i] = c;
        i++;
        if(c == '\n') {
            ch_str[i] = '\0';
            check_search(str, ch_str, &argc, argv);
            i = 0;
        }
    }
    ch_str[i] = '\n';
    ch_str[i+1] = '\0';
    check_search(str, ch_str, &argc, argv);
    if(ch_str) {
        free(ch_str);
    }
    fclose(ch);
}

void check_search(const char *str, char *ch_str, int **argc, char *argv) {
    int j = 0;
    char *ch_grep = NULL;
    for(int i = 0; ch_str[i] != '\0'; i++) {
        if(ch_str[i] == str[j]) {
            ch_grep = realloc(ch_grep, (j + 1) * sizeof(char));
            ch_grep[j] = str[j];
            j++;
            if(strlen(str) == j && strcmp(str, ch_grep) == 0) {
                output(ch_str, &argc, argv);
            }
        } else {
            j = 0;
        }
    }
    if(ch_grep) {
        free(ch_grep);
    }
}

void output(char *str, int ***argc, char *argv) {
    if(***argc > 3) {
        printf("%s:%s", argv, str);
    } else {
        printf("%s", str);
    }
}

int main(int argc, char *argv[]) {
    int arguments = 2;
    while(argv[arguments]) {
        if(cheking_file(argv[arguments]) == 0) {
            string_selection(argv[1], argv[arguments], &argc);
        }
        arguments++;
    }
    return 0;
}