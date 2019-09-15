#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "func.h"

unsigned int slen(const char *s) {
    const char *sc = s;
    while (*sc != '\0') {
        ++sc;
    }
    return sc - s;
}

short int scmp(const char *cs, const char *ct) {
    char c1, c2;

    while (1) {
        c1 = *cs++;
        c2 = *ct++;
        if (c1 != c2) {
            return c1 < c2 ? -1 : 1;
        }
        if (!c1) {
            break;
        }
    }
    return 0;
}

char *scpy(char *destination, const char *src) {
    char *temp = destination;
    while(*src != '\0') {
        *destination++ = *src++;
    }
    return temp;
}

unsigned int hash(char w)
{
    unsigned int h = 0;
    h = h * HASH_MUL + (unsigned int)w;
    return h % HASH_SIZE;
}

void search(char* buf, char* substr, int size, int substr_size)
{
    int ln = strlen(buf);
    int d[substr_size][size];
    int i, j, temp, r;
    char tmp;

    printf("this if buf - %s\n", buf);
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
        tmp = buf[j];
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
                printf("%c", buf[ex]);
                ex +=1;
            }
            printf("\n");
        }
    }
}

void open_txt(char* path, char* substr, int substr_size, int size)
{
    printf("%s\n", path);
    FILE *content = fopen(path, "r");
    if (content == NULL) {
        perror("Error: ");
        printf("Couldn't open file\n");
        return;
    }
    int T = 10,  i = 0, d = 10;
    char* buf = (char*)malloc(sizeof(char)*T);
    while ((buf[i] = fgetc(content)) != EOF) {
        if (++i>=T) {
            T+=d;
            buf = (char*)realloc(buf, sizeof(char)*T);
        }
    }
    buf[i] = '\0';
    fclose(content);
    /*if((fclose(content)) && (content)) {
        printf("Couldn't close file\n");
    }*/
    printf("%s", buf);
    search(buf, substr, size, substr_size);
    return;
}

void pathfind(char *substr, char *path, int substr_size, int size) {
    DIR* d;
    struct dirent *fold;
    const char* d_name;
    unsigned int ln;
    //d = opendir(substr);
    if ((d = opendir(substr)) != NULL) {
        /*while(1) {        
            fold = readdir(d);
            d_name = fold->d_name;
            unsigned int ln = slen(d_name);
            if (d_name[ln - 4] == '.' && d_name[ln - 3] == 't' && d_name[ln - 2] == 'x' && d_name[ln - 1] == 't') {
                char addname[50];
                scpy(addname, substr);
                ln = slen(addname);
                addname[ln + 1] = '/';
                strcat(addname, d_name);
                ln = slen(addname);
                addname[ln + 1] = '\0';
                open_txt(addname, substr, substr_size, size);
            }
            if(closedir(d) == 0) {
                printf("Couldn't close\n");
                perror("");
            }
        }*/
        while((fold = readdir(d)) != NULL) { //test iteration, view all files
            ln = slen(fold->d_name);
            d_name = fold->d_name;
            //printf("%d\n", ln);
            //printf("%c\n", d_name[ln - 1]);
            for (;;) {
            if(d_name[ln - 1] == 't') {
                if(d_name[ln - 2] == 'x') {
                    if(d_name[ln - 3] == 't') {
                        printf("txt - %s\n", fold->d_name);
                        char addname[80];
                	scpy(addname, substr);
                	ln = slen(addname);
                        printf("%d\n", ln);
                	/*addname[ln + 1] = '/';
			addname[ln + 2] = '\0';*/
                        printf("%s\n", addname);//check
                	strcat(addname, d_name);
                	ln = slen(addname);
                	addname[ln + 1] = '\0';
                	open_txt(addname, substr, substr_size, size);
                    } else {
                        break;
                    }
                } else {
                    break;
                }
            } else {
                break;
            }
            }
        }
        closedir(d); //end
    } else {
        printf("Can't open directory %s\n", substr);
        perror("");
        return;
    }
}

