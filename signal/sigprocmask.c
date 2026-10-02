#include <signal.h>
#include <errno.h>

extern long __flibc_syscall4(unsigned long n, unsigned long a1,
                             unsigned long a2, unsigned long a3,
                             unsigned long a4);

#define __NR_rt_sigprocmask 135

int sigprocmask(int how, const sigset_t *set, sigset_t *oldset) {
    long ret = __flibc_syscall4(__NR_rt_sigprocmask,
                                (unsigned long)how,
                                (unsigned long)set,
                                (unsigned long)oldset,
                                8);
    if (ret < 0 && ret > -4096) {
        errno = (int)(-ret);
        return -1;
    }
    return 0;
}
