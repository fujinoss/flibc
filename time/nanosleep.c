#include <time.h>
#include <errno.h>

extern long __flibc_syscall2(unsigned long n, unsigned long a1, unsigned long a2);

#define __NR_nanosleep 101

int nanosleep(const struct timespec *req, struct timespec *rem) {
    long ret = __flibc_syscall2(__NR_nanosleep,
                                (unsigned long)req,
                                (unsigned long)rem);
    if (ret < 0 && ret > -4096) {
        errno = (int)(-ret);
        return -1;
    }
    return 0;
}
