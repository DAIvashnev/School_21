#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

void check_key(char *argv, char **key);
int cheking_file(char *argv);
void string_selection(char *search_str, char *argv, int *argc);
int check_search(char *search_str, char *choice_str, char *argv);
void output(char *choice_str, char *argv, int **argc);

void check_key(char *argv, char **key) {
    if(argv[0] == '-') {
        *key = argv;
    }
}

int cheking_file(char *argv) {
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

void string_selection(char *search_str, char *argv, int *argc) {
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
            if(check_search(search_str, choice_str, argv) == 1) {
                output(choice_str, argv, &argc);
            }
            i = 0;
        }
    }
    choice_str[i] = '\n';
    choice_str[i+1] = '\0';
    if(check_search(search_str, choice_str, argv) == 1) {
        output(choice_str, argv, &argc);
    }
    free(choice_str);
    fclose(fp);
}

int check_search(char *search_str, char *choice_str, char *argv) {
    size_t j = 0;
    int flag = 0;
    char *check_str = NULL;
    for(int i = 0; choice_str[i] != '\0'; i++) {
        if(choice_str[i] == search_str[j]) {
            check_str = realloc(check_str, (j + 1) * sizeof(char));
            check_str[j] = search_str[j];
            j++;
            if(strlen(search_str) == j && strcmp(search_str, check_str) == 0) {
                flag = 1;
            }
        } else {
            j = 0;
        }
    }
    free(check_str);

    return flag;
}

void output(char *choice_str, char *argv, int **argc) {
    int check_flag = 0;
    if(**argc > 3) {
        printf("%s:%s", argv, choice_str);
    } else {
        printf("%s", choice_str);
    }
}

int main(int argc, char *argv[]) {
    int arguments = 0;
    char *key = "0";
    while(argv[arguments]) {
        check_key(argv[arguments], &key);
        arguments++;
    }
    if(key[0] == '-') { 
        arguments = 3; 
    } else { 
        arguments = 2; 
    }
    while(argv[arguments]) {
        if(cheking_file(argv[arguments]) == 0) {
            string_selection(argv[1], argv[arguments], &argc);
        }
        arguments++;
    }
    return 0;
}