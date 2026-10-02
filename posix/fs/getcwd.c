#include <unistd.h>
#include <errno.h>

extern long __flibc_syscall2(unsigned long n, unsigned long a1, unsigned long a2);

#define __NR_getcwd 17

char *getcwd(char *buf, size_t size) {
    long ret = __flibc_syscall2(__NR_getcwd, (unsigned long)buf, (unsigned long)size);
    if (ret < 0 && ret > -4096) {
        errno = (int)(-ret);
        return 0;
    }
    return buf;
}
