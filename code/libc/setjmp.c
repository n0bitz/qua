#include <setjmp.h>

char *__longjmp_target;
int __longjmp_value;
int __longjmp_skip;

int __setjmp(jmp_buf env) {
    if(!__longjmp_target) {
        __longjmp_skip = 0;
        return 0;
    }

    if(__longjmp_target == env) {
        __longjmp_target = 0;
        __longjmp_skip = 0;
        return __longjmp_value;
    }

    __longjmp_skip = 1;
    return 0;
}

void __longjmp(jmp_buf env, int status) {
    __longjmp_target = env;
    __longjmp_value = status ? status : 1;
}
