#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

void find_ch(const char *str, char *argv);

void find_ch(const char *str, char *argv) {
    FILE *ch;
    int c;
    char *ch_str = NULL;
    char ch_grep[1000];
    int i = 0;
    int j = 0;
    int k = 0;
    ch = fopen(argv, "r");
    while((c = getc(ch)) != EOF) {
        ch_str = realloc(ch_str, (i + 1) * sizeof(char));
        ch_str[i] = c;
        i++;
        if(c == '\n') {
            ch_str[i] = '\0';
            while(ch_str[j] != '\n') {
                if(ch_str[j] == str[k]) {
                    ch_grep[k] = str[k];
                    k++;
                    ch_grep[k] = '\0';
                } else {
                    k = 0;
                }
                if(strcmp(str, ch_grep) == 0) {
                    printf("%s\n", ch_str);
                    break;
                }
                j++;
            }
            j = 0;
            k = 0;
            i = 0;
        }
    }
    ch_str[i] = '\0';
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