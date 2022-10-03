#include <stdio.h>
#include <string.h>
#include <unistd.h>

void my_cat(char *argv, char key, int **num);
int check_key(char *check, int *argc, char *argv, int *num);

void my_cat(char *argv, char key, int **num) {
    FILE *fp;
    int c;
    fp = fopen(argv, "r");
    if(key == 'b') {
        int check = 0;
        while((c = getc(fp)) != EOF) {
            if(c != '\n' && check == 0) {
                check = 1;
                **num += 1;
                printf("     %d  ", **num);
            }
            putc(c, stdout);
            if(c == '\n') {
                check = 0;
            }
        }
        fclose(fp);
    } else if(key == 'n') {
        int ch_c = 10;
        while((c = getc(fp)) != EOF) {
            if(ch_c == 10) {
                **num += 1;
                printf("     %d  ", **num);
            }
            putc(c, stdout);
            ch_c = c;
        }
        fclose(fp);
    } else if(key == 'e') {
        while((c = getc(fp)) != EOF) {
            if(c == '\n') {
                printf("$");
            }
            putc(c, stdout);
        }
        fclose(fp);
    } else if(key == 'v') {
        while((c = getc(fp)) != EOF) {
            if((c < 33 && c != 9 && c != 10 && c != 13 && c != 32) || c == 127) {
                printf("^");
                printf("%c", c += 64);

            } else {
                putc(c, stdout);
            }
        }
        fclose(fp);
    } else if(key == 't') {
        while((c = getc(fp)) != EOF) {
            if(c == '\t') {
                printf("^I");
            }
            putc(c, stdout);
        }
        fclose(fp);
    } else if(key == 's') {
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
    } else {
        while((c = getc(fp)) != EOF) {
            putc(c, stdout);
        }
        fclose(fp);
    }
}

int check_key(char *check, int *argc, char *argv, int *num) {
    FILE *ch;
    char key = '0';
    int f = 0;
    char *n_der = "There is no such file or directory\n";
    char *inv_key = "my_cat: invalid key";
    if(check[0] != '-') {
        if((ch = fopen(argv, "r")) == NULL) {
            f = 2;
            printf("my_cat: %s: %s", argv, n_der);
        } else {
            f = 2;
            my_cat(argv, key, &num);
        }
    }
    if(f != 2){
        switch (check[1]) {
                case 'b' : 
                    if(*argc > 2 && check[2] == 0) {
                        if((ch = fopen(argv, "r")) == NULL) {
                            printf("my_cat: %s: %s", argv, n_der);
                        } else {
                            key = 'b';
                            my_cat(argv, key, &num);
                        }
                    } else {
                        printf("%s - «%s»\n", inv_key, check);
                        f = 1;
                    } break;
                case 'n' :
                if(*argc > 2 && check[2] == 0) {
                        if((ch = fopen(argv, "r")) == NULL) {
                            printf("my_cat: %s: %s", argv, n_der);
                        } else {
                            key = 'n';
                            my_cat(argv, key, &num);
                        }
                    } else {
                        printf("%s - «%s»\n", inv_key, check);
                        f = 1;
                    } break;
                case 'e' :
                    if(*argc > 2 && check[2] == 0) {
                        if((ch = fopen(argv, "r")) == NULL) {
                            printf("my_cat: %s: %s", argv, n_der);
                        } else {
                            key = 'e';
                            my_cat(argv, key, &num);
                        }
                    } else {
                        printf("%s - «%s»\n", inv_key, check);
                        f = 1;
                    } break;
                case 'v' :
                    if(*argc > 2 && check[2] == 0) {
                        if((ch = fopen(argv, "r")) == NULL) {
                            printf("my_cat: %s: %s", argv, n_der);
                        } else {
                            key = 'v';
                            my_cat(argv, key, &num);
                        }
                    } else {
                        printf("%s - «%s»\n", inv_key, check);
                        f = 1;
                    } break;
                case 't' :
                    if(*argc > 2 && check[2] == 0) {
                        if((ch = fopen(argv, "r")) == NULL) {
                            printf("my_cat: %s: %s", argv, n_der);
                        } else {
                            key = 't';
                            my_cat(argv, key, &num);
                        }
                    } else {
                        printf("%s - «%s»\n", inv_key, check);
                        f = 1;
                    } break;
                case 's' :
                    if(*argc > 2 && check[2] == 0) {
                        if((ch = fopen(argv, "r")) == NULL) {
                            printf("my_cat: %s: %s", argv, n_der);
                        } else {
                            key = 's';
                            my_cat(argv, key, &num);
                        }
                    } else {
                        printf("%s - «%s»\n", inv_key, check);
                        f = 1;
                    } break;
                default : 
                    if(f != 2) {
                        printf("%s - «%s»\n", inv_key, check); 
                        f = 1;
                        break;
                    }
            }
    }
    return f;
}

int main(int argc, char *argv[]) {
    char pt_c;
    if(argc == 1) {
        while(1) {
            scanf("%c", &pt_c);
            printf("%c", pt_c);
        }
    } else {
        int f = 0;
        int i = 0;
        int num = 0;
        char *check;
        while(*argv != NULL && f == 0) {
            check = *argv;
            if(check[0] == '-') {
                check = *argv;
                f = 1;
                if(i == 1) {
                    argv++;
                }
            }
            i++;
            argv++;
        }
        while(i != 0) {
            i--;
            argv--;
        }
        argv++;
        if(f == 1) {
            while(*argv && check_key(check,&argc,*argv,&num) == 0) {
                argv++;
                if(*argv == check) {
                    argv++;
                }
            }
        } else {
            while(*argv && check_key(check,&argc,*argv,&num) == 2 && f == 0) {
                argv++;
            }
        }
    }
    return 0;
}