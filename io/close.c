#include <unistd.h>
#include <errno.h>

extern long __flibc_syscall1(unsigned long n, unsigned long a1);

#define __NR_close 57

int close(int fd) {
    long ret = __flibc_syscall1(__NR_close, (unsigned long)fd);
    if (ret < 0 && ret > -4096) {
        errno = (int)(-ret);
        return -1;
    }
    return 0;
}
