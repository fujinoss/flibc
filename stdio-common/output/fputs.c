/* flibc — stdio-common/output/fputs.c
 *
 * Original work. Author: flibc contributors. License: MIT (see LICENSE).
 *
 * fputs — write a string to a fd-based stream. Currently only
 * supports stdout and stderr because we have no FILE yet.
 */

#include <stdio.h>
#include <string.h>

extern long __flibc_syscall3(unsigned long n, unsigned long a1,
                             unsigned long a2, unsigned long a3);

#define __NR_write 64

int fputs(const char *s, void *stream) {
    (void)stream;
    size_t n = strlen(s);
    __flibc_syscall3(__NR_write, 1, (unsigned long)s, (unsigned long)n);
    return (int)n;
}
