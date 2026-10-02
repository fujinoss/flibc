#include <signal.h>
#include <errno.h>
#include <stddef.h>

extern long __flibc_syscall4(unsigned long n, unsigned long a1,
                             unsigned long a2, unsigned long a3,
                             unsigned long a4);

#define __NR_rt_sigaction 134

extern void __flibc_restore_rt(void);

int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact) {
    struct sigaction local;
    if (act) {
        local = *act;
        if (local.sa_handler != SIG_DFL && local.sa_handler != SIG_IGN) {
            if (!(local.sa_flags & SA_RESTORER)) {
                local.sa_restorer = __flibc_restore_rt;
                local.sa_flags |= SA_RESTORER;
            }
        }
    }
    long ret = __flibc_syscall4(__NR_rt_sigaction,
                                (unsigned long)signum,
                                act ? (unsigned long)&local : 0,
                                (unsigned long)oldact,
                                8);
    if (ret < 0 && ret > -4096) {
        errno = (int)(-ret);
        return -1;
    }
    return 0;
}
