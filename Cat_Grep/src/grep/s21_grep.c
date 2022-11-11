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

int main (int argc, char *argv[]) {
    t_st structData;
    int arc = argc;
    //regex_t re;
    //regmatch_t match;
    //int error_regex;
    s21_in_Struct(&structData);
    for(size_t i = 1; argv[i] != NULL && structData.error_options == 0; i++) {
        parsingData(argv[i], &structData);
    }

    printf("%s\n%s\n%s\n%d\n", structData.key, structData.pattern, structData.file, structData.countArgument);
    printf("%d\n", arc);
    //regfree(&re);
    free_data(&structData);
    return 0;
}
