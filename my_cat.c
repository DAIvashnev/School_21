#include <stdio.h>
#include <string.h>

void my_cat(char *argv);

void my_cat(char *argv) {
    FILE *fp;
    int f = 0;
    int c;
    if((fp = fopen(argv, "r")) == NULL && f == 0) {
        printf("my_cat: %s: There is no such file or directory\n", argv);
        f = 1;
    } else if(f == 0) {
        while((c = getc(fp)) != EOF) {
            putc(c, stdout);
        }
        fclose(fp);
    }
}

int main(int argc, char *argv[]) {
    FILE *ch;
    char pt_c;
    if(argc == 1) {
        while(1) {
            scanf("%c", &pt_c);
            printf("%c", pt_c);
        }
    }
    char *check = argv[1];
    if(check[0] == '-') {
        switch (check[1]) {
            case 'n' :
                switch (check[2]) {
                    case '\0' : printf("HOOOLLLAAA\n"); break;
                    default : printf("my_cat: invalid key - «%s»\n", check); break;
                } break;
            case 'v' : 
                switch (check[2]) {
                    case '\0' : printf("777777777777\n"); break;
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
                my_cat(*argv);
            }
        }
    }
    return 0;
}