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

unsigned int slon(const char *s) {
    const char *sc = s;
    int k = 0; 
    while (*sc != '\0') {
        ++sc;
        if (*sc != '\n') {
        k++;    
        }
    }
    return sc - s - k;
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

void search(char* buf, char* substr)
{
    int ln = slen(buf);
    int i, j = 0, d, k = 0;
    int pref = slen(substr);
    //printf("this if buf - %s/end buf\n", buf);//buf's check
    //printf("Pref = %d\n", pref);
    //printf("ln = %d\n", ln);  

    while (j < ln) {
        d = 0;
        for(i = 0; i < pref; i++) {         
            //printf("i = %d\n", i);
            //printf("buf[j] = %c\n", buf[j]);
	    //printf("substr[i] = %c\n", substr[i]);
            if (buf[j] == substr[i]) {
                d++;
                j++;
                //printf("d = %d\n", d);
                if (d == pref) {
                    ++k;
                }
                //printf("k = %d\n", k);
            } else {
                j++;
                break;
            }     
        }
    }
    printf("%d Coincidence(s) was found out: %s\n", k, substr);
        return;
}

void open_txt(char* path, char* pref)
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
    search(buf, pref);
    return;
}

void pathfind(char *substr, char *path) {
    DIR* d;
    struct dirent *fold;
    const char* d_name;
    unsigned int ln;
    if ((d = opendir(substr)) != NULL) {
        while((fold = readdir(d)) != NULL) {
            ln = slen(fold->d_name);
            d_name = fold->d_name;
            for (;;) {
            if(d_name[ln - 1] == 't') {
                if(d_name[ln - 2] == 'x') {
                    if(d_name[ln - 3] == 't') {
                        char addname[80];
                	scpy(addname, substr);
                	ln = slen(addname);
                        //printf("%d\n", ln);
                	/*addname[ln + 1] = '/';
			addname[ln + 2] = '\0';*/
                        //printf("%s\n", addname);//check
                	strcat(addname, d_name);
                	ln = slen(addname);
                	addname[ln + 1] = '\0';
                	open_txt(addname, path);
                        for (int i = 0; i < ln; i++) {
                            addname[ln - i] = 0;
                        }
                        addname[ln + 1] = '\0';
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
        closedir(d);
    } else {
        printf("Can't open directory %s\n", substr);
        return;
    }
}

