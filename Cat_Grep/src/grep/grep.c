#include "header.h"

int data_key(char *argv, t_flags *countData) {
    int flag = 0;
    if(argv[0] == '-') {
        strcat(countData->key, argv);
        //countData->countArgument -= 1;
        countData->error_options = 1;
        checking_key(countData);
        flag = 1;
    }
    return flag;
}

void checking_key(t_flags *countData) {
    if(countData->key[0] == '-' && countData->key[2] == 0) {
        switch (countData->key[1]) {
            case 'e' : countData->e = 1; break;
            case 'i' : countData->i = 1; break;
            case 'v' : countData->v = 1; break;
            case 'c' : countData->c = 1; break;
            case 'l' : countData->l = 1; break;
            case 'n' : countData->n = 1; break;
            default : {
                printf("my_grep: invalid key - «%s»\n", countData->key); 
                countData->error_options = -1;
            }
        }

    } else {
        if(countData->key[1] != 'e') {
            printf("my_grep: invalid key - «%s»\n", countData->key); 
            countData->error_options = -1;
        } else {
            countData->e = 1;
        }
    }
}

int data_pattern(char *argv, t_flags *countData) {
    int flag = 0;
    if(argv[0] != '-') {
        strcat(countData->pattern, argv);
        flag = 1;
    }
    return flag;
}

int checking_file(char *argv, t_flags *countData) {
    FILE *fp;
    int flag = 0;
    if((fp = fopen(argv, "r")) == NULL) {
        if(argv[1] != countData->key[1] && argv[1] != countData->key[2]) {
            printf("my_grep: %s: There is no such file or directory\n", argv);
        }
        flag = 1;
    } else {
        fclose(fp);
    }
    return flag;
}

void regexData(t_flags *countData, regex_t *re, int *error_regex) {
    if(countData->e == 1 && (*error_regex = regcomp(re, countData->pattern, REG_NEWLINE | REG_EXTENDED)) == 0);
    else if(countData->i == 1 && (*error_regex = regcomp(re, countData->pattern, REG_NEWLINE | REG_ICASE)) == 0);
    else {
        regcomp(re, countData->pattern, REG_NEWLINE);
    }
}

void string_selection(char *argv, t_flags *countData, regex_t *re, regmatch_t *match, int *error_regex) {
    FILE *fp;
    int check_len;
    fp = fopen(argv, "r");
    if(countData->e == 1) {
        output_e(fp, argv, countData, re, match, error_regex);
    } else if(countData->v == 1) {
        output_v(fp, argv, countData, re, match, error_regex);
    } else if(countData->c == 1) {
        output_c(fp, argv, countData, re, match, error_regex);
    } else if(countData->l == 1) {
        output_l(fp, argv, countData, re, match, error_regex);
    } else if(countData->n == 1) {
        output_n(fp, argv, countData, re, match, error_regex);
    } else {
        while(fgets(countData->check_str, 256, fp) != NULL) {
            if((*error_regex = regexec(re, countData->check_str, 0, match, 0)) == 0) {
                check_len = strlen(countData->check_str);
                output(argv, countData);
                if(countData->check_str[check_len-1] != '\n') {
                    printf("\n");
                }

            }
        }
    }
    fclose(fp);
}

void output_e(FILE *fp, char *argv, t_flags *countData, regex_t *re, regmatch_t *match, int *error_regex) {
    int check_len;
    while(fgets(countData->check_str, 256, fp) != NULL) {
        if((*error_regex = regexec(re, countData->check_str, 0, match, 0)) == 0) {
            check_len = strlen(countData->check_str);
            output(argv, countData);
            if(countData->check_str[check_len-1] != '\n') {
                printf("\n");
            }
        }
    }
}

void output_v(FILE *fp, char *argv, t_flags *countData, regex_t *re, regmatch_t *match, int *error_regex) {
    int check_len;
    while(fgets(countData->check_str, 256, fp) != NULL) {
        if((*error_regex = regexec(re, countData->check_str, 0, match, 0)) != 0) {
            if(strcmp(countData->check_str, countData->pattern) != 0) {
                check_len = strlen(countData->check_str);
                output(argv, countData);
                if(countData->check_str[check_len-1] != '\n') {
                    printf("\n");
                }
            }
        }
    }
}

void output_c(FILE *fp, char *argv, t_flags *countData, regex_t *re, regmatch_t *match, int *error_regex) {
    int count = 0;
    while(fgets(countData->check_str, 256, fp) != NULL) {
        if((*error_regex = regexec(re, countData->check_str, 0, match, 0)) == 0) {
            count += 1;
        }
    }
    if(countData->countArgument > 3) {
        printf("%s:%d\n", argv, count);
    } else {
        printf("%d\n", count);
    }
}

void output_l(FILE *fp, char *argv, t_flags *countData, regex_t *re, regmatch_t *match, int *error_regex) {
    while(fgets(countData->check_str, 256, fp) != NULL) {
        if((*error_regex = regexec(re, countData->check_str, 0, match, 0)) == 0) {
            printf("%s\n", argv);
            break;
        }
    }
}

void output_n(FILE *fp, char *argv, t_flags *countData, regex_t *re, regmatch_t *match, int *error_regex) {
    int count = 0;
    while(fgets(countData->check_str, 256, fp) != NULL) {
        count += 1;
        if((*error_regex = regexec(re, countData->check_str, 0, match, 0)) == 0) {
            if(countData->countArgument > 3) {
                printf("%s:%d:%s", argv, count, countData->check_str);
            } else {
                printf("%d:%s", count, countData->check_str);
            }
        }
    }
}

void output(char *argv, t_flags *countData) {
    if(countData->countArgument > 3) {
        printf("%s:%s", argv, countData->check_str);
    } else {
        printf("%s", countData->check_str);
    }
}

int data_argv_e(char *argv, t_flags *countData) {
    int flag = 0;
    int len = 0;
    int i = 0;
    int j = 2;
    len = strlen(countData->pattern);
    if(argv[0] == '-' && argv[1] == 'e' && argv[2] != 0) {
        while(argv[j] != '\0') {
            countData->pattern[len] = argv[j];
            len++;
            j++;
        }
        countData->pattern[len] = '|';
        countData->countArgument -= 1;
    } else {
        while(argv[i] != '\0') {
            countData->pattern[len] = argv[i];
            len++;
            i++;
        }
        countData->pattern[len] = '|';
        countData->countArgument -= 2;
    }
    return flag;
}

int main(int argc, char *argv[]) {
    t_flags countData;
    regex_t re;
    regmatch_t match;
    int error_regex;
    s21_in_Struct(&countData);
    countData.countArgument = argc;
    printf("%d\n", countData.countArgument);
    for(size_t i = 1; argv[i] != NULL && data_key(argv[i], &countData) != 1; i++);
    if(countData.e == 0) {
        for(size_t i = 1; argv[i] != NULL && data_pattern(argv[i], &countData) != 1; i++);
    } else {
        for(size_t i = 1; argv[i] != NULL; i++) {
            if ((argv[i][0] == '-' && argv[i][1] == 'e' && argv[i][2] != 0) || (argv[i-1][1] == 'e' && argv[i-1][2] == 0)) {
                data_argv_e(argv[i], &countData);
            }
        }
        countData.pattern[strlen(countData.pattern)-1] = '\0';
    }
    regexData(&countData, &re, &error_regex);
    printf("%d\n", countData.countArgument);
    if(countData.error_options == 1) {
        for(size_t i = 1; i != (size_t)argc; i++) {
            if(strcmp(argv[i], countData.key) != 0 && checking_file(argv[i], &countData) == 0) {
                string_selection(argv[i], &countData,  &re, &match, &error_regex);
            }
        }
    } else if (countData.error_options == 0) {
        for(size_t i = 1; i != (size_t)argc; i++) {
            if(strcmp(argv[i], countData.key) != 0 && strcmp(argv[i], countData.pattern) != 0 && argv[i-1][1] != 'e' && checking_file(argv[i], &countData) == 0) {
                string_selection(argv[i], &countData, &re, &match, &error_regex);
            }
        }
    }
    regfree(&re);
    free_data(&countData);
    return 0;
}