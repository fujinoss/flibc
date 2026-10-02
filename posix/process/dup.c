#include <unistd.h>
#include <errno.h>

extern long __flibc_syscall1(unsigned long n, unsigned long a1);
extern long __flibc_syscall3(unsigned long n, unsigned long a1,
                             unsigned long a2, unsigned long a3);

#define __NR_dup  23
#define __NR_dup3 24

int dup(int oldfd) {
    long ret = __flibc_syscall1(__NR_dup, (unsigned long)oldfd);
    if (ret < 0 && ret > -4096) {
        errno = (int)(-ret);
        return -1;
    }
    return (int)ret;
}

int dup2(int oldfd, int newfd) {
    if (oldfd == newfd) return newfd;
    long ret = __flibc_syscall3(__NR_dup3,
                                (unsigned long)oldfd,
                                (unsigned long)newfd,
                                0);
    if (ret < 0 && ret > -4096) {
        errno = (int)(-ret);
        return -1;
    }
    return (int)ret;
}
