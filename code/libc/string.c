#include <string.h>

void* memchr(const void* ptr, int value, size_t num) {
    char *p = (char*)ptr;
    while(num && *p != value) {
        num--;
        p++;
    }
    if(num) {
        return (void*)p;
    } else {
        return NULL;
    }
}

int memcmp(const void* ptr1, const void* ptr2, size_t num) {
    const char* p1 = (char*)ptr1;
    const char* p2 = (char*)ptr2;
    while(num && *p1 == *p2) {
        num--;
        p1++;
        p2++;
    }
    if(num) {
        return *p1 - *p2;
    } else {
        return 0;
    }
}

int strncmp(const char* str1, const char* str2, size_t num){puts("strncmp");}

char* strerror(int errnum){
    return "Unknown error";
}

char* strpbrk(const char* str1, const char* str2) {
    while(*str1) {
        const char *c = str2;
        while(*c) {
            if(*str1 == *c) {
                return (char*)str1;
            }
            c++;
        }
        str1++;
    }
    return NULL;
} 

size_t strspn(const char* str1, const char* str2) {
    size_t len;
    const char* c;

    for(len = 0; *str1; str1++, len++) {
        for(c = str2; *c; c++) {
            if(*c == *str1) {
                break;
            }
        }
        if(!*c) {
            break;
        }
    }

    return len;
}

int strcoll(const char* str1, const char* str2){puts("strcoll");}
