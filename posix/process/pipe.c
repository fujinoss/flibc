#include <unistd.h>
#include <errno.h>

extern long __flibc_syscall2(unsigned long n, unsigned long a1, unsigned long a2);

#define __NR_pipe2 59

int pipe(int fds[2]) {
    long ret = __flibc_syscall2(__NR_pipe2, (unsigned long)fds, 0);
    if (ret < 0 && ret > -4096) {
        errno = (int)(-ret);
        return -1;
    }
    return 0;
}
