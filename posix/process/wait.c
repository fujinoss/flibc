#include <sys/wait.h>
#include <errno.h>

extern long __flibc_syscall4(unsigned long n, unsigned long a1,
                             unsigned long a2, unsigned long a3,
                             unsigned long a4);

#define __NR_wait4 260

pid_t waitpid(pid_t pid, int *status, int options) {
    long ret = __flibc_syscall4(__NR_wait4,
                                (unsigned long)(long)pid,
                                (unsigned long)status,
                                (unsigned long)options,
                                0);
    if (ret < 0 && ret > -4096) {
        errno = (int)(-ret);
        return -1;
    }
    return (pid_t)ret;
}

pid_t wait(int *status) {
    return waitpid(-1, status, 0);
}
