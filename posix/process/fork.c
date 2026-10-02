#include <unistd.h>
#include <errno.h>

extern long __flibc_syscall0(unsigned long n);

#define __NR_clone 220

#define SIGCHLD 17

pid_t fork(void) {
    long ret = __flibc_syscall0(__NR_clone);
    if (ret < 0 && ret > -4096) {
        errno = (int)(-ret);
        return -1;
    }
    return (pid_t)ret;
}
