#include "1header.h"

void parsingData(char *argv, t_st *structData) {
    if(argv[0] == '-') {
        data_key(argv, structData);
    } else if(argv[0] != '-' && structData->stopPattern == 0) {
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
    for(size_t i = 1; structData->key[i] != 0; i++) {
        switch (structData->key[i]) {
            case 'e' : structData->e = 1; break;
            case 'i' : structData->i = 1; break;
            case 'v' : structData->v = 1; break;
            case 'c' : structData->c = 1; break;
            case 'l' : structData->l = 1; break;
            case 'n' : structData->n = 1; break;
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
    if(structData->e == 1 && structData->i == 1 && (*error_regex = regcomp(re, structData->pattern, REG_NEWLINE | REG_EXTENDED | REG_ICASE)) == 0) {}
    if(structData->e == 1 && structData->i == 0 && (*error_regex = regcomp(re, structData->pattern, REG_NEWLINE | REG_EXTENDED)) == 0) {}
    if(structData->e == 0 && structData->i == 1 && (*error_regex = regcomp(re, structData->pattern, REG_NEWLINE | REG_ICASE)) == 0) {}
    else {
        regcomp(re, structData->pattern, REG_NEWLINE);
    }
}

int checking_file(t_st *structData, int *countFile) {
    FILE *fp;
    int flag = 0;
    int j = 0;
    while((structData->file[*countFile] != ' ' || structData->file[*countFile] != '\0') && flag == 0) {
        structData->check_file[j] = structData->file[*countFile];
        j++;
        *countFile += 1;
        if(structData->file[*countFile] == ' ' || structData->file[*countFile] == '\0') {
            *countFile += 1;
            structData->check_file[j] = '\0';
            if((fp = fopen(structData->check_file, "r")) == NULL) {
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
    //printf("-%s-\n", structData->check_file);
    //printf("VSE OKKK!!!\n");
    FILE *fp;
    int check_len;
    fp = fopen(structData->check_file, "r");
    if(structData->e == 1) {
        //output_e(fp, structData->check_file, structData, re, match, error_regex);
    } else if(structData->v == 1) {
        //output_v(fp, structData->check_file, structData, re, match, error_regex);
    } else if(structData->c == 1) {
        //output_c(fp, structData->check_file, structData, re, match, error_regex);
    } else if(structData->l == 1) {
        //output_l(fp, structData->check_file, structData, re, match, error_regex);
    } else if(structData->n == 1) {
        //output_n(fp, structData->check_file, structData, re, match, error_regex);
    } else {
        while(fgets(structData->check_str, 256, fp) != NULL) {
            if((*error_regex = regexec(re, structData->check_str, 0, match, 0)) == 0) {
                check_len = strlen(structData->check_str);
                output(structData);
                if(structData->check_str[check_len-1] != '\n') {
                    printf("\n");
                }

            }
        }
    }
    fclose(fp);
}

void output(t_st *structData) {
    if(structData->countArgument > 1) {
        printf("%s:%s", structData->check_file, structData->check_str);
    } else {
        printf("%s", structData->check_str);
    }
}

int main (int argc, char *argv[]) {
    t_st structData;
    regex_t re;
    regmatch_t match;
    int error_regex;
    int arc = argc;         //временно
    s21_in_Struct(&structData);
    for(size_t i = 1; argv[i] != NULL && structData.error_options == 0; i++) {
        parsingData(argv[i], &structData);
    }
    if(structData.countArgument != 0) {
        regexData(&re, &error_regex, &structData);
        int countFile = 0;
        for(size_t i = 0; i != (size_t)structData.countArgument; i++) {
            if(checking_file(&structData, &countFile) != 1) {
                search_matches(&re, &match, &error_regex, &structData);
            }
        }
    }

    //printf("%s\n%s\n-%s-\n%d\n", structData.key, structData.pattern, structData.file, structData.countArgument); //временно
    //printf("\n-%s-\n", structData.str_file); //временно
    printf("%d\n", arc);        //временно
    regfree(&re);
    free_data(&structData);
    return 0;
}
