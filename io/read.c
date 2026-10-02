#include <unistd.h>
#include <errno.h>

extern long __flibc_syscall3(unsigned long n, unsigned long a1,
                             unsigned long a2, unsigned long a3);

#define __NR_read 63

ssize_t read(int fd, void *buf, size_t count) {
    long ret = __flibc_syscall3(__NR_read,
                                (unsigned long)fd,
                                (unsigned long)buf,
                                (unsigned long)count);
    if (ret < 0 && ret > -4096) {
        errno = (int)(-ret);
        return -1;
    }
    return (ssize_t)ret;
}
