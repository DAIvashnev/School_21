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
    if(check[0] != '-') {
        if((ch = fopen(argv, "r")) == NULL) {
            f = 2;
            printf("my_cat: %s: There is no such file or directory\n", argv);
        } else {
            f = 2;
            my_cat(argv, key, &num);
        }
    }
    switch (check[1]) {
            case 'b' : 
                if(*argc > 2 && check[2] == 0) {
                    if((ch = fopen(argv, "r")) == NULL) {
                        printf("my_cat: %s: There is no such file or directory\n", argv);
                    } else {
                        key = 'b';
                        my_cat(argv, key, &num);
                    }
                } else {
                    printf("my_cat: invalid key - «%s»\n", check);
                    f = 1;
                } break;
            case 'n' :
               if(*argc > 2 && check[2] == 0) {
                    if((ch = fopen(argv, "r")) == NULL) {
                        printf("my_cat: %s: There is no such file or directory\n", argv);
                    } else {
                        key = 'n';
                        my_cat(argv, key, &num);
                    }
                } else {
                    printf("my_cat: invalid key - «%s»\n", check);
                    f = 1;
                } break;
            default : 
                if(f != 2) {
                    printf("my_cat: invalid key - «%s»\n", check); 
                    f = 1;
                    break;
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
        argv++;
        while(*argv != NULL && f == 0) {
            check = *argv;
            if(check[0] == '-') {
                check = *argv;
                f = 1;
            }
            i++;
            argv++;
        }
        while(i != 0) {
            i--;
            argv--;
        }
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