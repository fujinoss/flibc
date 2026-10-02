#include <time.h>
#include <errno.h>

struct timeval {
    long tv_sec;
    long tv_usec;
};

extern long __flibc_syscall2(unsigned long n, unsigned long a1, unsigned long a2);

#define __NR_gettimeofday 169

int gettimeofday(struct timeval *tv, void *tz);

int gettimeofday(struct timeval *tv, void *tz) {
    (void)tz;
    long ret = __flibc_syscall2(__NR_gettimeofday, (unsigned long)tv, 0);
    if (ret < 0 && ret > -4096) {
        errno = (int)(-ret);
        return -1;
    }
    return 0;
}
