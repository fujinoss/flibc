#include <signal.h>
#include <unistd.h>
#include <errno.h>

extern long __flibc_syscall2(unsigned long n, unsigned long a1, unsigned long a2);
extern long __flibc_syscall1(unsigned long n, unsigned long a1);

#define __NR_kill 129
#define __NR_getpid 172

int kill(pid_t pid, int sig) {
    long ret = __flibc_syscall2(__NR_kill, (unsigned long)(long)pid, (unsigned long)sig);
    if (ret < 0 && ret > -4096) {
        errno = (int)(-ret);
        return -1;
    }
    return 0;
}

int raise(int sig) {
    pid_t pid = (pid_t)__flibc_syscall1(__NR_getpid, 0);
    return kill(pid, sig);
}
