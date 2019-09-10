#include "func.h"
#include <stdio.h>

int main(int argc, char *argv[]) {

    if (!argv[0] || !argv[1] || !argv[2]) {
        printf("Incorrect number of arguments\n");
        return 0;
    }
    if ((scmp(argv[0], "./fsmatcher") == 0) || (scmp(argv[0], "./fs-gdb") == 0)) {
        char *substr = argv[2];
        int substr_size = slen(substr);
        int size = 30;
        pathfind(argv[2], argv[1], substr_size, size);
    } else {
        printf("Wrong argument\n");
        return 0;
    }
    return 0;
}
