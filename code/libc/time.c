#include <time.h>

clock_t clock(void) {
    clock_t t;
    puts("clock");
    return t;
}

time_t time(time_t* timer){
    puts("time");
    if(timer) *timer = 0;
    return 0;
}
