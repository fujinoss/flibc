/* flibc — io/write.c
 *
 * Original work. Author: flibc contributors. License: MIT (see LICENSE).
 *
 * write(2) — write bytes to a file descriptor.
 *
 * Calls __flibc_syscall3 (aarch64 svc #0 wrapper exported from
 * arch/aarch64/syscalls.zig). On error, sets errno and returns -1.
 */

#include <unistd.h>
#include <errno.h>

extern long __flibc_syscall3(unsigned long n,
                             unsigned long a1,
                             unsigned long a2,
                             unsigned long a3);

#define __NR_write 64

ssize_t write(int fd, const void *buf, size_t count) {
    long ret = __flibc_syscall3(__NR_write,
                                (unsigned long)fd,
                                (unsigned long)buf,
                                (unsigned long)count);
    if (ret < 0 && ret > -4096) {
        errno = (int)(-ret);
        return -1;
    }
    return (ssize_t)ret;
}
