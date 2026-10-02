#include <fcntl.h>
#include <errno.h>
#include <stdarg.h>

extern long __flibc_syscall4(unsigned long n, unsigned long a1,
                             unsigned long a2, unsigned long a3,
                             unsigned long a4);

#define __NR_openat 56

int openat(int dirfd, const char *path, int flags, ...) {
    unsigned int mode = 0;
    if (flags & O_CREAT) {
        va_list ap;
        va_start(ap, flags);
        mode = (unsigned int)va_arg(ap, int);
        va_end(ap);
    }
    long ret = __flibc_syscall4(__NR_openat,
                                (unsigned long)(long)dirfd,
                                (unsigned long)path,
                                (unsigned long)flags,
                                (unsigned long)mode);
    if (ret < 0 && ret > -4096) {
        errno = (int)(-ret);
        return -1;
    }
    return (int)ret;
}
