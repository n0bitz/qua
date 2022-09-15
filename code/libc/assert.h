#ifndef __ASSERT_H
#define __ASSERT_H

#include <stdio.h>

#ifdef NDEBUG
#define assert(condition) ((void)0)
#else
#define assert(condition) ((condition) || (printf("Assertion %s failed\n", #condition), abort(), 0))
#endif

#endif
