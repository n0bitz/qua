#include <stddef.h>
#include <stdlib.h>
#include <string.h>

typedef struct __malloc_chunk{
    size_t size;
    struct __malloc_chunk* next;
} __malloc_chunk;

#define CHUNK_TO_USER_DATA(chunk) ((void*)(chunk + 1))
#define USER_DATA_TO_CHUNK(data) (((__malloc_chunk*)data) - 1)
#define USABLE_SIZE(size) ((size) - sizeof(__malloc_chunk))

char __malloc_buf[8*1024*1024];
__malloc_chunk *__free_list;
int __malloc_initialized;
size_t __malloc_used;

void trap_Error(const char*);
void abort(void) {
    trap_Error("abort");
}

void* calloc(size_t nmemb, size_t size) {
    void* p = malloc(nmemb * size);
    memset(p, 0, nmemb * size);
    return p;
}

char* getenv(const char* name){
    return NULL;
}

void __init_malloc(void) {
    __malloc_chunk* chunk = (__malloc_chunk*)__malloc_buf;
    chunk->size = sizeof(__malloc_buf);
    __free_list = chunk;
    __malloc_initialized = 1;
}

void* malloc(size_t size) {
    __malloc_chunk* chunk;
    __malloc_chunk** next;

    if(!__malloc_initialized) {
        __init_malloc();
    }

    size += sizeof(__malloc_chunk);
    size = (size + 3) & ~3;

    // find a big enough free chunk
    next = &__free_list;
    while(*next) {
        chunk = *next;
        if(chunk->size >= size) {
            break;
        }
        next = &chunk->next;
    }

    if(!*next) {
        return NULL;
    }

    // unlink from free list
    *next = chunk->next;

    // split off extra space if possible
    if(chunk->size >= size + sizeof(__malloc_chunk)) {
        __malloc_chunk* split = (__malloc_chunk*)((char*)chunk + size);
        split->size = chunk->size - size;
        split->next = __free_list;
        __free_list = split;
        chunk->size = size;
    }

    __malloc_used += chunk->size;
    return CHUNK_TO_USER_DATA(chunk);
}

void* realloc(void* ptr, size_t size) {
    if(ptr) {
        if(size == 0) {
            free(ptr);
            return NULL;
        } else {
            size_t old_size = USABLE_SIZE(USER_DATA_TO_CHUNK(ptr)->size);
            void* new_ptr = malloc(size);
            memcpy(new_ptr, ptr, old_size > size ? size : old_size);
            free(ptr);
            return new_ptr;
        }
    } else {
        return malloc(size);
    }
}

void free(void* ptr){
    __malloc_chunk* chunk;
    __malloc_chunk** next;

    if(!ptr) {
        return;
    }

    chunk = USER_DATA_TO_CHUNK(ptr);

    // merge with adjacent chunks
    // TODO maybe doubly link to avoid linearly scanning through all free chunks
    next = &__free_list;
    while(*next) {
        __malloc_chunk* other = *next;
        if((char*)chunk + chunk->size == (char*)other) {
            __malloc_used += other->size;
            chunk->size += other->size;
            *next = other->next;
        } else if((char*)other + other->size == (char*)chunk) {
            __malloc_used += other->size;
            other->size += chunk->size;
            chunk = other;
            *next = other->next;
        } else {
            next = &other->next;
        }
    }

    chunk->next = __free_list;
    __free_list = chunk;
    __malloc_used -= chunk->size;
}
