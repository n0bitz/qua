#include <limits.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include "../qcommon/q_shared.h"

static void __print(const char* s) {
    trap_Print(s);
}

FILE __stdin, *stdin = &__stdin;
FILE __stdout, *stdout = &__stdout;
FILE __stderr, *stderr = &__stderr;

void clearerr(FILE* stream) {
    stream->eof = 0;
    stream->error = 0;
}

int fclose(FILE* stream) {
    trap_FS_FCloseFile(stream->handle);
    free(stream);
}

int feof(FILE* stream) {
    return stream->eof;
}

int ferror(FILE* stream) {
    return stream->error;
}

int fflush(FILE* stream) {
    return 0;
}

char* fgets(char* str, int num, FILE* stream){puts("fgets");}

FILE* fopen(const char* filename, const char* mode) {
    FILE* f;
    int modeval;

    f = calloc(1, sizeof(FILE));
    if(!f) {
        return NULL;
    }

    if(strcmp(mode, "r") == 0 || strcmp(mode, "rb") == 0) {
        modeval = FS_READ;
    } else if(strcmp(mode, "w") == 0 || strcmp(mode, "wb") == 0) {
        modeval = FS_WRITE;
    } else {
        fprintf(stderr, "fopen: unsupported mode %s\n", mode);
        abort();
    }

    trap_FS_FOpenFile(filename, &f->handle, modeval);
    if(!f->handle) {
        free(f);
        return NULL;
    }

    return f;
}

int fprintf(FILE* stream, const char* format, ...){
    char buf[4906];
    int len;
    va_list va;
    va_start(va, format);
    len = vsnprintf(buf, sizeof(buf), format, va);
    fwrite(buf, len, 1, stream);
    va_end(va);
    return len;
}

size_t fread(void* ptr, size_t size, size_t count, FILE* stream) {
    size_t len = size * count;

    if(trap_FS_Read(ptr, len, stream->handle) != len) {
        stream->eof = 1;
        return 0;
    }

    return len;
}

FILE* freopen(const char* filename, const char* mode, FILE* stream){puts("freopen");}
int fseek(FILE* stream, long int offset, int origin){puts("fseek");}
long int ftell(FILE* stream){puts("int");}

size_t fwrite(const void* ptr, size_t size, size_t count, FILE* stream) {
    if(stream == stdout || stream == stderr) {
        __print((const char*)ptr);
    } else {
        if(!trap_FS_Write(ptr, size * count, stream->handle)) {
            stream->error = 1;
        }
    }
    return size * count;
}

int getc(FILE* stream) {
    char c;
    if(fread(&c, 1, 1, stream) != 1) {
        return EOF;
    }
    return c;
}

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
    return printf("%s\n", s);
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
