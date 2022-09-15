#ifndef __STDDEF_H
#define __STDDEF_H

#include <stdint.h>

#define NULL ((void*)0)
#define offsetof(type, member) ((size_t)((char*)&((type*)0)->member - (char*)0))

typedef unsigned size_t;
typedef int ptrdiff_t;

#endif
