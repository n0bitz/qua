#ifndef __STDIO_H
#define __STDIO_H

#include <stddef.h>

#define EOF (-1)
#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2

#define _IOFBF 0
#define _IOLBF 1
#define _IONBF 2

#define BUFSIZ 1

typedef struct {
    int todo;
} FILE;

extern FILE* stdin;
extern FILE* stdout;
extern FILE* stderr;

void clearerr(FILE*);
int fclose(FILE*);
int feof(FILE*);
int ferror(FILE*);
int fflush(FILE*);
char* fgets(char*, int, FILE*);
FILE* fopen(const char*, const char*);
int fprintf(FILE*, const char*, ...);
size_t fread(void*, size_t, size_t, FILE*);
FILE* freopen(const char*, const char*, FILE*);
int fseek(FILE*, long int, int);
long int ftell(FILE*);
size_t fwrite(const void*, size_t, size_t, FILE*);
int getc(FILE*);
int printf(const char*, ...);
int setvbuf(FILE*, char*, int, size_t);
int sprintf(char*, const char*, ...);
FILE* tmpfile(void);
int ungetc(int, FILE*);

#endif
