#include <stdio.h>
#include <stdarg.h>
#include <sys/types.h>

extern void __flibc_vformat(void (*sink)(void *, const char *, size_t),
                            void *ctx, const char *fmt, va_list ap);

typedef struct { char *buf; size_t cap; size_t pos; } bufctx;

static void buf_sink(void *ctx, const char *data, size_t len) {
    bufctx *b = ctx;
    for (size_t i = 0; i < len && b->pos + 1 < b->cap; i++) {
        b->buf[b->pos++] = data[i];
    }
}

int vsnprintf(char *buf, size_t n, const char *fmt, va_list ap) {
    bufctx b = { buf, n, 0 };
    if (n == 0) return 0;
    __flibc_vformat(buf_sink, &b, fmt, ap);
    buf[b.pos] = '\0';
    return (int)b.pos;
}

int snprintf(char *buf, size_t n, const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    int r = vsnprintf(buf, n, fmt, ap);
    va_end(ap);
    return r;
}
