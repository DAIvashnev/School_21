#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    FILE *fp;
    int f = 0;
    int c;
    char *check = argv[1];
    if(check[0] == '-') {
        f = 1;
        switch (check[1]) {
            case 'n' :
                printf("HOOOLLLAAA\n"); break;
            case 'v' :
                printf("777777777777\n"); break;
            default :
                printf("my_cat: %s: There is no such file or directory\n", *argv); break;
        }
    }
    while(*argv) {
        if((fp = fopen(*++argv, "r")) == NULL && f == 0) {
            printf("my_cat: %s: There is no such file or directory\n", *argv);
            f = 1;
        } else if(f == 0) {
            while((c = getc(fp)) != EOF) {
                putc(c, stdout);
            }
            fclose(fp);
        }
        if((fp = fopen(*++argv, "r")) == NULL) {
            if(*argv == NULL) {
                break;
            }
            printf("my_cat: %s: There is no such file or directory\n", *argv);
        } else {
            *--argv;
            fclose(fp);
        }
    }
    return f;
}