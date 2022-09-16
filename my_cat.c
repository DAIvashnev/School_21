#include <stdio.h>
#include <string.h>

void my_cat(char *argv, char key, int *num);

void my_cat(char *argv, char key, int *num) {
    FILE *fp;
    int f = 0;
    int c;
    if((fp = fopen(argv, "r")) == NULL && f == 0) {
        printf("my_cat: %s: There is no such file or directory\n", argv);
        f = 1;
    } else if(f == 0) {
        if(key == 'b') {
            int check = 0;
            while((c = getc(fp)) != EOF) {
                if(c != '\n' && check == 0) {
                    check = 1;
                    *num += 1;
                    printf("%d  ", *num);
                }
                putc(c, stdout);
                if(c == '\n') {
                    check = 0;
                }
            }
            fclose(fp);
        }
        /*while((c = getc(fp)) != EOF) {
            putc(c, stdout);
        }
        fclose(fp);*/
    }
}

int main(int argc, char *argv[]) {
    FILE *ch;
    char pt_c;
    char key;
    int num = 0;
    if(argc == 1) {
        while(1) {
            scanf("%c", &pt_c);
            printf("%c", pt_c);
        }
    }
    char *check = argv[1];
    if(check[0] == '-') {
        switch (check[1]) {
            case 'b' : 
                if(argc >= 2) {
                    while(*argv) {
                        argv++;
                        if((ch = fopen(*argv, "r")) == NULL) {
                            if(*argv == NULL) {
                                break;
                            }
                            if(!(argv[1])) {
                                printf("my_cat: %s: There is no such file or directory\n", *argv);
                            }
                        } else {
                            key = 'b';
                            my_cat(*argv, key, &num);
                        }
                    }
                } break;
            case 'n' :
                switch (check[2]) {
                    case '\0' : printf("HOOOLLLAAA\n"); break;
                    default : printf("my_cat: invalid key - «%s»\n", check); break;
                } break;
            default : printf("my_cat: invalid key - «%s»\n", check); break;
        }
    } else {
        while(*argv) {
            argv++;
            if((ch = fopen(*argv, "r")) == NULL) {
                if(*argv == NULL) {
                    break;
                }
                printf("my_cat: %s: There is no such file or directory\n", *argv);
            } else {
                my_cat(*argv, key, &num);
            }
        }
    }
    return 0;
}