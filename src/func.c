#include "func.h"

void open_txt(char* path, char* substr, int size, int substr_size)
{
    FILE *content = fopen(path, "r");
    if (content == NULL) {
        printf("Couldn't open file\n");
        return;
    }
    int T = 10,  i = 0;
    char* buf = (char*)malloc(sizeof(char)*T);
    while ((buf[i] = fgetc(content)) != EOF) {
        if (++i>=T) {
            T+=10;
            buf = (char*)realloc(buf, sizeof(char)*T);
        }
    }
    buf[i] = '\0';
    fclose(content);
    search(path, substr, size, substr_size);
    return;
}

void pathfind(char* pathname, int substr_size, int size, char* substr)
{
    DIR* d;
    d = opendir(pathname);
    if (!d) {
        printf("Can't open directory %s\n", pathname);
        return;
    }
    while(1) {
        struct dirent *inc;
        const char * d_name;
        inc = readdir(d);
        if (!inc) {
            break;
        }
        d_name = inc->d_name;
        int ln = strlen(d_name);
        if (d_name[ln - 1] == 't' && d_name[ln - 2] == 'x' && d_name[ln - 3] == 't') {
            printf("\n%s/%s\n", pathname, d_name);
            char addlen[50];//dinamic massive!!
            strcpy(addlen, pathname);
            /*ln = strlen(addlen);
            addlen[ln] = '/';
            addlen[ln + 1] = '\0';*/
            open_txt(addlen, substr, size, substr_size);
        }
        if(closedir(d)) {
            printf("Couldn't close\n");
        }
    }
}

unsigned int hash(char w)
{
    unsigned int h = 0;
    h = h * HASH_MUL + (unsigned int)w;
    return h % HASH_SIZE;
}

void search(char* path, char* substr, int size, int substr_size)
{
    int ln = strlen(path);
    int d[substr_size][size];
    int i, j, temp, r;
    char tmp;

    r = hash('*');
    for(i = 0; i < substr_size; i++) {
        for(j = 0; j < size; j++) {
            d[i][j] = 0;
        }
    }

    for(i = 0; i < substr_size; i++) {
        tmp = substr[i];
        if(tmp == '?') {
            for(j = 0; j < size; j++) {
                d[i][j] = i + 1;
            }
            d[i][r] = 0;
        } else {
              temp = hash(tmp);
              j = d[i][temp];
              d[i][temp] = i + 1;
              if (i == 0) {
                  for (j = 0; j < substr_size; j++) {
                      d[j][temp] = d[i][temp];
                  }
              }
        }
    }

    for(i = 0; i < substr_size; i++) {
        if(d[i][r] != 0) {
            if((i + 1) < substr_size) {
                for(j = 0; j < size; j++) {
                    d[i][j] = i;
                }
                for(j = 0; j < size; j++) {
                    if(d[i + 1][j] == i + 2) {
                        d[i][j] = i + 2;
                    }
                }
             } else {
                  for (j = 0; j < size; j++) {
                      d[i][j] = i + 1;
                  }
             }
         }
    }
    int k = 0;
    for(j = 0; j < ln; j++) {
        tmp = path[j];
        temp = hash(tmp);
        i = d[i][temp];
        if(i == 1) {
            k = j;
        }
        if ((i == 1) && (d[i][r] != 1)) {
            k = j;
        }
        if (i == substr_size) {
            j = 0;
            printf("\nFind %d mathes\n", k + 1);
            int ex = k;
            while(ex <= k) {
                printf("%c", path[ex]);
                ex +=1;
            }
            printf("\n");
        }
    }
}
