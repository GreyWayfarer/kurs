#include "func.h"

int main(int argc, char *argv[])
{
    if (!argv[0] || !argv[1] || !argv[2]) {
        printf("Incorrent number of arguments\n");
        return 0;
    }
    char *substr = argv[1];
    int substr_size = strlen(substr);
    int size = 30;

    if((strcmp(argv[0], "./fsmatcher") == 0) || (strcmp(argv[0], "./fs-gdb") == 0)) {
        pathfind(argv[2], substr_size, size, substr);
    } else {
        printf("Wrong argument\n");
        return 0;
    }
    return 0;
}



/*int compute_trans(char p, char) {
    m = strlen(p);
    for(q = 0; q < m; q++) {
        k = min(m + 1, q + 2);
        while() {
            k--;
            scheme(q, a) = k;
        }
    }
    return scheme();
}*/
