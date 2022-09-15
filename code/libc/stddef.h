#ifndef __STDDEF_H
#define __STDDEF_H

#include <stdint.h>

#ifndef NULL
#define NULL ((void*)0)
#endif

#define offsetof(type, member) ((size_t)((char*)&((type*)0)->member - (char*)0))

#ifndef BG_LIB_H
typedef unsigned size_t;
#endif

typedef int ptrdiff_t;

#endif
