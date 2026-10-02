#include <time.h>
#include <errno.h>

extern long __flibc_syscall2(unsigned long n, unsigned long a1, unsigned long a2);

#define __NR_clock_gettime 113
#define __NR_clock_getres  114

int clock_gettime(int clk, struct timespec *tp) {
    long ret = __flibc_syscall2(__NR_clock_gettime,
                                (unsigned long)clk,
                                (unsigned long)tp);
    if (ret < 0 && ret > -4096) {
        errno = (int)(-ret);
        return -1;
    }
    return 0;
}

int clock_getres(int clk, struct timespec *tp) {
    long ret = __flibc_syscall2(__NR_clock_getres,
                                (unsigned long)clk,
                                (unsigned long)tp);
    if (ret < 0 && ret > -4096) {
        errno = (int)(-ret);
        return -1;
    }
    return 0;
}
