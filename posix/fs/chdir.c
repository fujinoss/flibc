#include <unistd.h>
#include <errno.h>

extern long __flibc_syscall1(unsigned long n, unsigned long a1);

#define __NR_chdir 49

int chdir(const char *path) {
    long ret = __flibc_syscall1(__NR_chdir, (unsigned long)path);
    if (ret < 0 && ret > -4096) {
        errno = (int)(-ret);
        return -1;
    }
    return 0;
}
