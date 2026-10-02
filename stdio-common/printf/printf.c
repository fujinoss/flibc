#include <stdio.h>
#include <stdarg.h>
#include <sys/types.h>

extern void __flibc_vformat(void (*sink)(void *, const char *, size_t),
                            void *ctx, const char *fmt, va_list ap);
extern long __flibc_syscall3(unsigned long n, unsigned long a1,
                             unsigned long a2, unsigned long a3);

#define __NR_write 64

static void write_sink(void *ctx, const char *data, size_t len) {
    (void)ctx;
    __flibc_syscall3(__NR_write, 1, (unsigned long)data, (unsigned long)len);
}

int printf(const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    __flibc_vformat(write_sink, 0, fmt, ap);
    va_end(ap);
    return 0;
}
