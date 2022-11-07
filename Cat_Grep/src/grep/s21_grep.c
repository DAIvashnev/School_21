#include "struct.h"

int data_key(char *argv, t_flags *countData) {
    int flag = 0;
    if(argv[0] == '-') {
        if(countData->key[0] == '-') {
            strcat(countData->key, argv);
            countData->key[2] = countData->key[3];
            countData->key[3] = '\0';
            countData->countArgument -= 1;
        } else {
            strcat(countData->key, argv);
            countData->countArgument -= 1;
        }
    }
    return flag;
}

int data_pattern(char *argv, t_flags *countData) {
    int flag = 0;
    if(argv[0] != '-') {
        strcat(countData->pattern, argv);
        flag = 1;
    }
    return flag;
}

int checking_key(t_flags *countData) {
    int flag = 0;
    if(countData->key[0] == '-') {
        for(size_t i = 1; countData->key[i] != 0; i++) {
            switch (countData->key[i]) {
                case 'e' : countData->e = 1; break;
                case 'i' : countData->i = 1; break;
                case 'v' : countData->v = 1; break;
                case 'c' : countData->c = 1; break;
                case 'l' : countData->l = 1; break;
                case 'n' : countData->n = 1; break;
                default : {
                    printf("my_grep: invalid key - «%s»\n", countData->key); 
                    flag = -1;
                }
            }

        }
    }
    return flag;
}

int checking_file(char *argv, t_flags *countData) {
    FILE *fp;
    int flag = 0;
    int c;
    if((fp = fopen(argv, "r")) == NULL) {
        if(argv[1] != countData->key[1] && argv[1] != countData->key[2]) {
            printf("my_grep: %s: There is no such file or directory\n", argv);
        }
        flag = 1;
    } else if((c = getc(fp)) == EOF) {
        flag = 1;
        fclose(fp);
    } else {
        fclose(fp);
    }
    return flag;
}

void string_selection(char *argv, t_flags *countData) {
    FILE *fp;
    char check_str[100];
    char *estr;
    fp = fopen(argv, "r");
    while(1) {
        estr = fgets(check_str, 100, fp);
        if(estr == NULL) {
            int c = strlen(check_str);
            if(strstr(check_str, countData->pattern) != 0 && check_str[c] != '\n') {
                printf("\n");
            }
            break;
        } else if(strstr(check_str, countData->pattern) != 0) {
            output(check_str, argv, countData);
        }
    }
    fclose(fp);
}

void output(char *choice_str, char *argv, t_flags *countData) {
    if(countData->countArgument > 3) {
        printf("%s:%s", argv, choice_str);
    } else {
        printf("%s", choice_str);
    }
}

int main(int argc, char *argv[]) {
    t_flags countData;
    s21_in_Struct(&countData);
    countData.countArgument = argc;
    for(size_t i = 1; argv[i] != NULL && data_key(argv[i], &countData) != 1; i++);
    for(size_t i = 1; argv[i] != NULL && data_pattern(argv[i], &countData) != 1; i++);
    for(size_t i = 1; i != (size_t)argc && checking_key(&countData) == 0; i++) {
        if(strcmp(argv[i], countData.key) != 0 && strcmp(argv[i], countData.pattern) != 0 && checking_file(argv[i], &countData) == 0) {
            string_selection(argv[i], &countData);
        }
    }
    free_data(&countData);
    return 0;
}