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
                break;
        }
    }
    if((fp = fopen(*++argv, "r")) == NULL && f == 0) {
        printf("error: can't open %s\n", *argv);
        f = 1;
    } else if(f == 0) {
        int p = 0;
        while((c = getc(fp)) != EOF) {
            p++;
            putc(c, stdout);
        }
        if(p == 0) {
            printf("File %s is empty.\n", *argv);
        }
        fclose(fp);
    }
    
    return f;
}