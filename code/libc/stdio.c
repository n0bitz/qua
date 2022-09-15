#include <stdio.h>
#include <stdarg.h>
#include <limits.h>

int Q_vsnprintf(char*, size_t, const char*, va_list);
void trap_Print(const char*);

static void __print(const char* s) {
    trap_Print(s);
}

FILE __stdin, *stdin = &__stdin;
FILE __stdout, *stdout = &__stdout;
FILE __stderr, *stderr = &__stderr;

void clearerr(FILE* stream){puts("clearerr");}
int fclose(FILE* stream){puts("fclose");}
int feof(FILE* stream){puts("feof");}
int ferror(FILE* stream){puts("ferror");}

int fflush(FILE* stream) {
    return 0;
}

char* fgets(char* str, int num, FILE* stream){puts("fgets");}
FILE* fopen(const char* filename, const char* mode){puts("fopen");}

int fprintf(FILE* stream, const char* format, ...){
    char buf[4906];
    int result;
    va_list va;
    va_start(va, format);
    result = vsnprintf(buf, sizeof(buf), format, va);
    // if(stream == stdout || stream == stderr) {
    __print(buf);
    // }
    va_end(va);
    return result;
}

size_t fread(void* ptr, size_t size, size_t count, FILE* stream){puts("fread");}
FILE* freopen(const char* filename, const char* mode, FILE* stream){puts("freopen");}
int fseek(FILE* stream, long int offset, int origin){puts("fseek");}
long int ftell(FILE* stream){puts("int");}

size_t fwrite(const void* ptr, size_t size, size_t count, FILE* stream) {
    // if(stream == stdout || stream == stderr) {
    __print((const char*)ptr);
    // }
}

int getc(FILE* stream){puts("getc");}

int printf(const char* format, ...) {
    char buf[4096];
    int result;
    va_list va;
    va_start(va, format);
    result = vsnprintf(buf, sizeof(buf), format, va);
    va_end(va);
    __print(buf);
    return result;
}

int puts(const char *s) {
    fprintf(stdout, "%s\n", s);
    return 0;
}

int setvbuf(FILE* stream, char* buffer, int mode, size_t size){puts("setvbuf");}

int sprintf(char* str, const char* format, ...) {
    int result;
    va_list va;
    va_start(va, format);
    result = vsnprintf(str, SIZE_MAX, format, va);
    va_end(va);
    return result;
}

int vsnprintf(char* str, size_t length, const char* format, va_list args) {
    return Q_vsnprintf(str, length, format, args);
}

FILE* tmpfile(void){puts("tmpfile");}
int ungetc(int character, FILE* stream){puts("ungetc");}
