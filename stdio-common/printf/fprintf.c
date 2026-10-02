#include <stdio.h>
#include <stdarg.h>
#include <sys/types.h>

extern void __flibc_vformat(void (*sink)(void *, const char *, size_t),
                            void *ctx, const char *fmt, va_list ap);
extern size_t fwrite(const void *ptr, size_t size, size_t n, FILE *f);

static void file_sink(void *ctx, const char *data, size_t len) {
    fwrite(data, 1, len, (FILE *)ctx);
}

int fprintf(FILE *f, const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    __flibc_vformat(file_sink, f, fmt, ap);
    va_end(ap);
    return 0;
}
