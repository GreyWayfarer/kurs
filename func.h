#ifndef FUNC_H
#define FUNC_H

#include "func.h" 
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <limits.h>
#define HASH_MUL 31
#define HASH_SIZE 26

unsigned int slen(const char *s);

unsigned int slon(const char *s);

short int scmp(const char *cs, const char *ct);

char *scpy(char *destination, const char *src);

void open_txt(char* path, char* substr);

void pathfind(char *substr, char *path);

unsigned int hash(char w);

void search(char* path, char* substr);

#endif
