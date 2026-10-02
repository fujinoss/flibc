/* flibc — stdio-common/output/puts.c
 *
 * Original work. Author: flibc contributors. License: MIT (see LICENSE).
 *
 * puts — write a string followed by a newline to stdout.
 */

#include <stdio.h>
#include <string.h>

extern long __flibc_syscall3(unsigned long n, unsigned long a1,
                             unsigned long a2, unsigned long a3);

#define __NR_write 64

int puts(const char *s) {
    size_t n = strlen(s);
    __flibc_syscall3(__NR_write, 1, (unsigned long)s, (unsigned long)n);
    __flibc_syscall3(__NR_write, 1, (unsigned long)"\n", 1);
    return (int)(n + 1);
}
