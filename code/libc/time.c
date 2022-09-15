#include <stddef.h>
#include <time.h>

int trap_RealTime(void*);

clock_t clock(void) {
    clock_t t;
    puts("clock");
    return t;
}

time_t time(time_t* timer){
    return trap_RealTime(NULL);
}
