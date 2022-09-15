#ifndef __STDLIB_H
#define __STDLIB_H

#include <stddef.h>

void abort(void);
int abs(int);
char* getenv(const char*);
void* malloc(size_t);
void* realloc(void*, size_t);
void free(void*);
double strtod(const char*, char**);

#endif
