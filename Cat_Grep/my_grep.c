#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

void find_ch(const char *str, char *argv);
void check_string(const char *str, char *ch_str);

void check_string(const char *str, char *ch_str) {
    int j = 0;
    char *ch_grep = NULL;
    for(int i = 0; ch_str[i] != '\0'; i++) {
        if(ch_str[i] == str[j]) {
            ch_grep = realloc(ch_grep, (j + 1) * sizeof(char));
            ch_grep[j] = str[j];
            j++;
            if(strlen(str) == j && strcmp(str, ch_grep) == 0) {
                printf("%s", ch_str);
            }
        } else {
            j = 0;
        }
    }
    free(ch_grep);
}

void find_ch(const char *str, char *argv) {
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
            check_string(str, ch_str);
            i = 0;
        }
    }
    ch_str[i] = '\n';
    ch_str[i+1] = '\0';
    check_string(str, ch_str);
    free(ch_str);
    fclose(ch);
}

int main(int argc, char *argv[]) {
    FILE *fp;
    if((fp = fopen(argv[2], "r")) != NULL) {
        find_ch(argv[1], argv[2]);
    }else {
        printf("my_grep: %s: There is no such file or directory\n", argv[2]);
    }
    return 0;
}