#ifndef FUNC_H
#define FUNC_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#define HASH_MUL 31
#define HASH_SIZE 26

void open_txt(char* path, char* string, int size, int substr_size);

void pathfind(char* pathname, int substr_size, int size, char *substr);

unsigned int hash(char w);

void search(char* path, char* substr, int size, int substr_size);

#endif
