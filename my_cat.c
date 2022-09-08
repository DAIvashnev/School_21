#include <stdio.h>

int main(int argc, char *argv[]) {
    FILE *fp;
    int f = 0;
    int c;
    if((fp = fopen(*++argv, "r")) == NULL) {
        printf("error: can't open %s\n", *argv);
        f = 1;
    } else if(f == 0) {
        while((c = getc(fp)) != EOF) {
            putc(c, stdout);
        }
        fclose(fp);
    }
    
    return f;
}