#include "s21_grep_header.h"

void s21_grep_help(const char *argv, t_st *structData) {
    free_data(structData);
    if((argv[0] == '-' && structData->help_grep <= 2) || ((structData->e == 1 || structData->f == 1) && structData->help_grep <= 2)) {
        printf("s21_grep SYNOPSIS: grep [options] PATTERN [FILE...]\n");
    } else {
        printf("s21_grep SYNOPSIS: grep [options] PATTERN [FILE...]\n");
    }
}

void parsingData(char *argv, t_st *structData) {
    if(argv[0] == '-') {
        data_key(argv, structData);
    } else if(structData->stopPattern == 0) {
        data_pattern(argv, structData);
    } else {
        data_file(argv, structData);
    }
}

void data_key(char *argv, t_st *structData) {
    strcat(structData->key, argv);
    checking_key(structData);
    structData->key[0] = '\0';
}

void checking_key(t_st *structData) {
    for(size_t i = 1; structData->key[i] != 0 && structData->error_options == 0; i++) {
        switch (structData->key[i]) {
            case 'e' : structData->e = 1; break;
            case 'i' : structData->i = 1; break;
            case 'v' : structData->v = 1; break;
            case 'c' : structData->c = 1; break;
            case 'l' : structData->l = 1; break;
            case 'n' : structData->n = 1; break;
            case 'o' : structData->o = 1; break;
            case 'h' : structData->h = 1; break;
            case 's' : structData->s = 1; break;
            case 'f' : structData->f = 1; break;
            default : {
                printf("my_grep: invalid key - «%c»\n", structData->key[i]);
                structData->error_options = -1;
            }
        }
    }
}

void data_pattern(char *argv, t_st *structData) {
    strcat(structData->pattern, argv);
    structData->stopPattern = 1;
}

void data_file(char *argv, t_st *structData) {
    if(structData->countArgument != 0) {
        structData->file[strlen(structData->file)] = ' ';
    }
    strcat(structData->file, argv);
    structData->countArgument += 1;
}

void regexData(regex_t *re, int *error_regex, t_st *structData) {
    if((structData->e == 1 || structData->f == 1) && structData->i == 1 && (*error_regex = regcomp(re, structData->pattern, REG_NEWLINE | REG_EXTENDED | REG_ICASE)) == 0) {}
    else if((structData->e == 1 || structData->f == 1) && structData->i == 0 && (*error_regex = regcomp(re, structData->pattern, REG_NEWLINE | REG_EXTENDED)) == 0) {}
    else if((structData->e == 0 && structData->f == 0) && structData->i == 1 && (*error_regex = regcomp(re, structData->pattern, REG_NEWLINE | REG_ICASE)) == 0) {}
    else {
        regcomp(re, structData->pattern, REG_NEWLINE);
    }
}

int checking_file(t_st *structData, int *countFile, int *check_s) {
    FILE *fp;
    int flag = 0;
    int j = 0;
    while((structData->file[*countFile] != '\0') && flag == 0) {
        structData->check_file[j] = structData->file[*countFile];
        j++;
        *countFile += 1;
        if(structData->file[*countFile] == ' ' || structData->file[*countFile] == '\0') {
            *countFile += 1;
            structData->check_file[j] = '\0';
            if((fp = fopen(structData->check_file, "r")) == NULL && structData->s == 1) {
                *check_s = 1;
                break;
            }
            if((fp = fopen(structData->check_file, "r")) == NULL && structData->s != 1) {
                printf("my_grep: %s: There is no such file or directory\n", structData->check_file);
                flag = 1;
            } else {
                fclose(fp);
                break;
            }
        }
    }
    return flag;
}

void search_matches(regex_t *re, regmatch_t *match, int *error_regex, t_st *structData) {
    FILE *fp;
    fp = fopen(structData->check_file, "r");
    if(structData->v == 1 && structData->c == 0 && structData->l == 0 && structData->o == 0) {
        output_v(fp, structData, re, match, error_regex);
    } else if(structData->c == 1 && structData->l == 0) {
        output_c(fp, structData, re, match, error_regex);
    } else if(structData->l == 1) {
        output_l(fp, structData, re, match, error_regex);
    } else if(structData->n == 1 && structData->v == 0 && structData->o == 0) {
        output_n(fp, structData, re, match, error_regex);
    } else if(structData->o == 1 && structData->v == 0) {
        strcat(structData->o_pattern, structData->pattern);
        output_o(fp, structData, re, match, error_regex);
    } else {
        while(fgets(structData->check_str, 256, fp) != NULL && structData->v != 1 && structData->o != 1 && structData->empty_file == 0) {
            if((*error_regex = regexec(re, structData->check_str, 0, match, 0)) == 0) {
                output(structData);
            }
        }
    }
    fclose(fp);
}

void output_v(FILE *fp, t_st *structData, regex_t *re, regmatch_t *match, int *error_regex) {
    while(fgets(structData->check_str, 256, fp) != NULL) {
        structData->countOutput += 1;
        if((*error_regex = regexec(re, structData->check_str, 0, match, 0)) != 0) {
            if(strcmp(structData->check_str, structData->pattern) != 0) {
                if(structData->n == 1) {
                    count_output(structData);
                } else {
                    output(structData);
                }
            }
        }
    }
    structData->countOutput = 0;
}

void output_c(FILE *fp, t_st *structData, regex_t *re, regmatch_t *match, int *error_regex) {
    while(fgets(structData->check_str, 256, fp) != NULL) {
        if((*error_regex = regexec(re, structData->check_str, 0, match, 0)) == 0 && structData->v == 0) {
            structData->countOutput += 1;
        } else if ((*error_regex = regexec(re, structData->check_str, 0, match, 0)) != 0 &&structData->v == 1) {
            structData->countOutput += 1;
        }
    }
    if(structData->countArgument > 1 && structData->h == 0) {
        printf("%s:%d\n", structData->check_file, structData->countOutput);
    } else {
        printf("%d\n", structData->countOutput);
    }
    structData->countOutput = 0;
}

void output_l(FILE *fp, t_st *structData, regex_t *re, regmatch_t *match, int *error_regex) {
    while(fgets(structData->check_str, 256, fp) != NULL) {
        if((*error_regex = regexec(re, structData->check_str, 0, match, 0)) == 0) {
            printf("%s\n", structData->check_file);
            break;
        }
    }
}

void output_n(FILE *fp, t_st *structData, regex_t *re, regmatch_t *match, int *error_regex) {
    while(fgets(structData->check_str, 256, fp) != NULL) {
        structData->countOutput += 1;
        if((*error_regex = regexec(re, structData->check_str, 0, match, 0)) == 0) {
            count_output(structData);
        }
    }
    structData->countOutput = 0;
}

void output_o(FILE *fp, t_st *structData, regex_t *re, regmatch_t *match, int *error_regex) {
    char *check = calloc(256, sizeof(char));
    int x = 0;
    int j = 0;
    while(fgets(structData->check_str, 256, fp) != NULL) {
        structData->countOutput += 1;
        if((*error_regex = regexec(re, structData->check_str, 0, match, 0)) == 0) {
            for(int i = 0; structData->o_pattern[i] != '\0'; i++) {
                check[j] = structData->o_pattern[i];
                j++;
                if(structData->o_pattern[i+1] == '|' || structData->o_pattern[i+1] == '\0') {
                    check[j] = '\0';
                    for(int k = 0; structData->check_str[k] != '\0'; k++) {
                        if(structData->i == 1) {
                            if(toupper(check[x]) == structData->check_str[k] || tolower(check[x]) == structData->check_str[k]) {
                                structData->o_search[x] = structData->check_str[k];
                                x++;
                            } else {
                                x = 0;
                                structData->o_search[x] = '\0';
                            }
                        } else {
                            if(check[x] == structData->check_str[k]) {
                                structData->o_search[x] = structData->check_str[k];
                                x++;
                            } else {
                                x = 0;
                                structData->o_search[x] = '\0';
                            }
                        }
                        if(check[x] == '\0') {
                            structData->o_search[x] = '\0';
                            x = 0;
                            if(strcasecmp(structData->o_search, check) == 0) {
                                if(structData->n == 1) {
                                    count_output(structData);
                                } else {
                                    output(structData);
                                }
                            }
                        } 
                    }
                    j = 0;
                    i++;
                }
            }
        }
    }
    structData->countOutput = 0;
    free(check);
}

void data_argv_e(const char *argv, t_st *structData) {
    int len = 0;
    len = strlen(structData->pattern);
    if(argv[0] == '-' && argv[1] == 'e' && argv[2] != 0) {
        int j = 2;
        while(argv[j] != '\0') {
            structData->pattern[len] = argv[j];
            len++;
            j++;
        }
        structData->pattern[len] = '|';
    } else {
        int i = 0;
        while(argv[i] != '\0') {
            structData->pattern[len] = argv[i];
            len++;
            i++;
        }
        structData->pattern[len] = '|';
    }
}

void data_argv_f(const char *argv, t_st *structData) {
    FILE *fp;
    int len = 0;
    int i = 0;
    int j = 2;
    len = strlen(structData->pattern);
    if(argv[0] == '-' && argv[1] == 'f' && argv[2] != 0) {
        while(argv[j] != '\0') {
            structData->check_argv_f[i] = argv[j];
            i++;
            j++;
        }
    } else {
        while(argv[i] != '\0') {
            structData->check_argv_f[i] = argv[i];
            i++;
            j++;
        }
    }
    structData->check_argv_f[i] = '\0';
    struct stat stat_record;
    if((fp = fopen(structData->check_argv_f, "r")) == NULL) {
        printf("my_grep: %s: There is no such file or directory\n", structData->check_argv_f);
        structData->error_f_file = 1;
    } 
    if(stat(structData->check_argv_f, &stat_record));
    else if(stat_record.st_size <= 1) {
        if(!(strlen(structData->pattern))) {
            structData->empty_file = 1;
        }
    } else {
        structData->empty_file = 0;
        int c;
        while((c = getc(fp)) != EOF) {
            if(c == '\n') {
                c = '|';
            }
            structData->pattern[len] = c;
            len++;
        }
        structData->pattern[strlen(structData->pattern)] = '|';
    }
    if(fp != NULL) {
        fclose(fp);
    }
}

void output(t_st *structData) {
    if(structData->countArgument > 1 && structData->h == 0) {
        if(structData->o == 1 && structData->v == 0 && structData->c == 0 && structData->l == 0) {
            printf("%s:%s\n", structData->check_file, structData->o_search);
        } else {
            printf("%s:%s", structData->check_file, structData->check_str);
        }
    } else {
        if(structData->o == 1 && structData->v == 0 && structData->c == 0 && structData->l == 0) {
            printf("%s\n", structData->o_search);
        } else {
            printf("%s", structData->check_str);
        }
    }
    if(structData->o != 1) {
        structData->check_len = strlen(structData->check_str);
        if(structData->check_str[structData->check_len-1] != '\n') {
            printf("\n");
        }
        structData->check_len = 0;
    }
}

void count_output(t_st *structData) {
    if(structData->countArgument > 1 && structData->h == 0) {
        if(structData->o == 1 && structData->v == 0 && structData->c == 0 && structData->l == 0) {
            printf("%s:%d:%s\n", structData->check_file, structData->countOutput, structData->o_search);
        } else {
            printf("%s:%d:%s", structData->check_file, structData->countOutput, structData->check_str);
        }
    } else {
        if(structData->o == 1 && structData->v == 0 && structData->c == 0 && structData->l == 0) {
            printf("%d:%s\n", structData->countOutput, structData->o_search);
        } else {
            printf("%d:%s", structData->countOutput, structData->check_str);
        }
    }
    if(structData->o != 1) {
        structData->check_len = strlen(structData->check_str);
        if(structData->check_str[structData->check_len-1] != '\n') {
            printf("\n");
        }
        structData->check_len = 0;
    }
}

int main (int argc, char *argv[]) {
    t_st structData;
    s21_in_Struct(&structData);
    regex_t re;
    regmatch_t match;
    int error_regex;

    for(size_t i = 1; argv[i] != NULL; i++) {
        if(argv[i][0] == '-' && argv[i][1] == 'e') {
            structData.e = 1;
        }
        if(argv[i][0] == '-' && argv[i][1] == 'f') {
            structData.f = 1;
        }
    }
    
    if(structData.f == 1) {
        for(size_t i = 1; argv[i] != NULL && structData.error_f_file != 1; i++) {
            if ((argv[i][0] == '-' && argv[i][1] == 'f' && argv[i][2] != 0) || (argv[i-1][1] == 'f' && argv[i-1][2] == 0)) {
                data_argv_f(argv[i], &structData);
            } 
        }
    }

    if(structData.e == 0 && structData.f == 0) {
        for(size_t i = 1; argv[i] != NULL && structData.error_options == 0; i++) {
            parsingData(argv[i], &structData);
        }
    } else {
        for(size_t i = 1; argv[i] != NULL && structData.error_f_file != 1; i++) {
            if(argv[i+1] == NULL && argv[i][0] == '-' && (argv[i][1] == 'e' || argv[i][1] == 'f') && argv[i][2] == 0) {
                structData.countArgument = 0;
            }
            
            if((argv[i][0] == '-' && argv[i][1] == 'e' && argv[i][2] != 0) || (argv[i-1][1] == 'e' && argv[i-1][2] == 0)) {
                data_argv_e(argv[i], &structData);
            } else if(argv[i][1] != 'e' && argv[i][0] != '-') {
                if(!((argv[i][0] == '-' && argv[i][1] == 'f' && argv[i][2] != 0) || (argv[i-1][1] == 'f' && argv[i-1][2] == 0)) && argv[i][1] != 'f') {
                    data_file(argv[i], &structData);
                }
            } else if(argv[i][1] != 'e' && argv[i][1] != 'f'){
                data_key(argv[i], &structData);
            }
        }
        structData.pattern[strlen(structData.pattern)-1] = '\0';
    }

    if(structData.countArgument != 0 && structData.error_f_file != 1) {
        regexData(&re, &error_regex, &structData);
        int countFile = 0;
        int check_s = 0;
        for(size_t i = 0; i != (size_t)structData.countArgument && structData.error_options == 0; i++) {
            if(checking_file(&structData, &countFile, &check_s) != 1 && check_s != 1) {
                search_matches(&re, &match, &error_regex, &structData);
            }
            check_s = 0;
        }
        regfree(&re);
        free_data(&structData);
    } else if(structData.error_f_file != 1) {
        structData.help_grep = argc;
        s21_grep_help(argv[1], &structData);
    }
    return 0;
}
