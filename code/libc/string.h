#ifndef __STRING_H
#define __STRING_H

#include <stddef.h>

void* memchr(const void*, int, size_t);
int memcmp(const void*, const void*, size_t);
void* memcpy(void*, const void*, size_t);
void* memset(void*, int, size_t);
char* strchr(const char*, int);
int strcmp(const char*, const char*);
int strncmp(const char*, const char*, size_t);
char* strcpy(char*, const char*);
char* strerror(int);
size_t strlen(const char*);
char* strpbrk(const char*, const char*); 
char* strstr(const char*, const char*);
size_t strspn(const char*, const char*);
int strcoll(const char*, const char*);

#endif
