#include <stdlib.h>
#include <string.h>

char* getenv(const char* name){puts("getenv");}

char __malloc_buf[8*1024*1024];
size_t __malloc_offset;

void* malloc(size_t size) {
    size += sizeof(size_t);
    size = ((size + 3) / 4) * 4;
    if(__malloc_offset < sizeof(__malloc_buf) - size) {
        char *p = __malloc_buf + __malloc_offset;
        __malloc_offset += size;
        memset(p, 0, size);
        ((size_t*)p)[0] = size;
        return p + sizeof(size_t);
    }
    return NULL;
}

void* realloc(void* ptr, size_t size) {
    if(ptr) {
        void *new_ptr = NULL;
        if(size) {
            size_t old_size = ((size_t*)ptr)[-1] - sizeof(size_t);
            new_ptr = malloc(size);
            memcpy(new_ptr, ptr, old_size);
        }
        free(ptr);
        return new_ptr;
    } else {
        return malloc(size);
    }
}

void free(void* ptr){}
