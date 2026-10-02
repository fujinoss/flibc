#include <unistd.h>
#include <errno.h>

extern long __flibc_syscall3(unsigned long n, unsigned long a1,
                             unsigned long a2, unsigned long a3);

#define __NR_execve 221

int execve(const char *path, char *const argv[], char *const envp[]) {
    long ret = __flibc_syscall3(__NR_execve,
                                (unsigned long)path,
                                (unsigned long)argv,
                                (unsigned long)envp);
    if (ret < 0 && ret > -4096) {
        errno = (int)(-ret);
        return -1;
    }
    return 0;
}
