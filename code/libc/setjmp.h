#ifndef __SETJMP_H
#define __SETJMP_H

typedef char jmp_buf[1];
extern char *__longjmp_target;

int __setjmp(jmp_buf env);
void __longjmp(jmp_buf env, int status);
#define setjmp(env) __setjmp(env)
#define longjmp(env, status) __longjmp(env, status)

#endif
