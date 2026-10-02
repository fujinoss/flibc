#include <stdlib.h>

extern long __flibc_syscall1(unsigned long n, unsigned long a1);

#define __NR_exit_group 94

void _exit(int code) {
    __flibc_syscall1(__NR_exit_group, (unsigned long)(code & 0xff));
    __builtin_unreachable();
}
