#ifndef __TIME_H
#define __TIME_H

typedef struct {
    int todo;
} clock_t;

typedef unsigned time_t;

clock_t clock(void);
time_t time(time_t*);

#endif
