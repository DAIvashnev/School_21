#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if(argv[1] == NULL && argc == 1) {
        char *c = "grep";
        printf("%s\n", c);
    }
    return 0;
}