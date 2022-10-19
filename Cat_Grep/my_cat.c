#include <stdio.h>
#include <string.h>
#include <unistd.h>

int data_key(char *argv, char **key);
int checking_key(char *argv, char *key);
void show_nonprinting(char *argv, int *c, char *key);
void output(char *argv, char *key, int *num);

int data_key(char *argv, char **key) {
    int flag = 0;
    if(argv[0] == '-') {
        *key = argv;
        flag = 1;
    }
    return flag;
}

int checking_key(char *argv, char *key) {
    FILE *ch;
    int flag = 0;
    if(key[2] == 0 && key[0] != '0') {
        if(!(key[1] == 'b' || key[1] == 'n' || key[1] == 's' || key[1] == 'e' || key[1] == 'v' || key[1] == 't')) {
            printf("my_cat: invalid key - «%s»\n", key);
            flag = 1;
        }
    } else if(key[0] != '0') {
        printf("my_cat: invalid key - «%s»\n", key);
        flag = 1;
    }
    if((ch = fopen(argv, "r")) == NULL && flag != 1) {
        printf("my_cat: %s: There is no such file or directory\n", argv);
    }
    return flag;
}

void show_nonprinting(char *argv, int *c, char *key) {
    FILE *sn;
    sn = fopen(argv, "r");
    while((*c = getc(sn)) != EOF) {
        if(key[1] == 'e' && *c == '\n') {
            printf("$");
        }
        if(key[1] == 't' && *c == '\t') {
            *c = 73;
            printf("^");
        }
        if((*c < 33 && *c != 9 && *c != 10 && *c != 13 && *c != 32) || *c == 127) {
            printf("^");
            if(*c + 64 < 128) {
                printf("%c", *c += 64);
            } else {
                *c = 128 - 127 + 62;
                printf("%c", *c);
            }

        } else {
            putc(*c, stdout);
        }
    }
    fclose(sn);
}

void output(char *argv, char *key, int *num) {
    FILE *fp;
    int c;
    fp = fopen(argv, "r");
    if(key[1] == 'b') {
        int check = 0;
        while((c = getc(fp)) != EOF) {
            if(c != '\n' && check == 0) {
                check = 1;
                *num += 1;
                printf("%6d\t", *num);
            }
            putc(c, stdout);
            if(c == '\n') {
                check = 0;
            }
        }
        fclose(fp);
    } else if(key[1] == 'n') {
        int ch_c = 10;
        while((c = getc(fp)) != EOF) {
            if(ch_c == '\n') {
                *num += 1;
                printf("%6d\t", *num);
            }
            putc(c, stdout);
            ch_c = c;
        }
        fclose(fp);
    } else if(key[1] == 's') {
        int f = 1;
        while((c = getc(fp)) != EOF) {
            if(c == '\n') {
                f++;
            } else {
                f = 0;
            }
            if(f <= 2) {
                putc(c, stdout);
            }
        }
        fclose(fp);
    } else if(key[1] == 'e' || key[1] == 'v' || key[1] == 't') {
        show_nonprinting(argv, &c, key);
    } else {
        while((c = getc(fp)) != EOF) {
            putc(c, stdout);
        }
        fclose(fp);
    }
}

int main(int argc, char *argv[]) {
    int num = 0;
    int result_key = argc;
    char *key = "0";
    for(size_t i = 0; argv[i] != NULL && key[0] != '-'; i++) {
        result_key = data_key(argv[i], &key);
    }
    if(result_key == 1) {
        for(size_t i = 2; argv[i] != NULL && checking_key(argv[i], key) != 1; i++) {
            output(argv[i], key, &num);
        }
    } else {
        for(size_t i = 1; argv[i] != NULL; i++) {
            output(argv[i], key, &num);
        }
    }
    return 0;
}