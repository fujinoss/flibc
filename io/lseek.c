#include <unistd.h>
#include <errno.h>

extern long __flibc_syscall3(unsigned long n, unsigned long a1,
                             unsigned long a2, unsigned long a3);

#define __NR_lseek 62

off_t lseek(int fd, off_t offset, int whence) {
    long ret = __flibc_syscall3(__NR_lseek,
                                (unsigned long)fd,
                                (unsigned long)offset,
                                (unsigned long)whence);
    if (ret < 0 && ret > -4096) {
        errno = (int)(-ret);
        return -1;
    }
    return (off_t)ret;
}
