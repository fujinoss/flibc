#include <stdio.h>
#include <stdarg.h>
#include <stddef.h>

typedef void (*sink_fn)(void *ctx, const char *data, size_t len);

static int fmt_uint(char *buf, unsigned long long v, int base, int upper) {
    const char *digits = upper ? "0123456789ABCDEF" : "0123456789abcdef";
    char tmp[24];
    int n = 0;
    if (v == 0) { tmp[n++] = '0'; }
    else { while (v) { tmp[n++] = digits[v % base]; v /= base; } }
    for (int i = 0; i < n; i++) buf[i] = tmp[n - 1 - i];
    return n;
}

static void pad(sink_fn sink, void *ctx, char c, int n) {
    while (n-- > 0) sink(ctx, &c, 1);
}

void __flibc_vformat(sink_fn sink, void *ctx, const char *fmt, va_list ap) {
    while (*fmt) {
        if (*fmt != '%') {
            const char *s = fmt;
            while (*fmt && *fmt != '%') fmt++;
            sink(ctx, s, (size_t)(fmt - s));
            continue;
        }
        fmt++;
        if (*fmt == '%') { sink(ctx, "%", 1); fmt++; continue; }

        int flag_left = 0, flag_zero = 0;
        while (*fmt == '-' || *fmt == '0') {
            if (*fmt == '-') flag_left = 1;
            if (*fmt == '0') flag_zero = 1;
            fmt++;
        }
        int width = 0;
        while (*fmt >= '0' && *fmt <= '9') width = width * 10 + (*fmt++ - '0');
        int is_long = 0, is_llong = 0;
        if (*fmt == 'l') { is_long = 1; fmt++; if (*fmt == 'l') { is_llong = 1; fmt++; } }
        else if (*fmt == 'z') { is_long = 1; fmt++; }

        char buf[24];
        int len = 0, neg = 0;
        const char *str = 0;
        int slen = 0;

        switch (*fmt) {
            case 'd': case 'i': {
                long long v = is_llong ? va_arg(ap, long long) :
                              is_long  ? va_arg(ap, long) :
                                         va_arg(ap, int);
                if (v < 0) { neg = 1; v = -v; }
                len = fmt_uint(buf, (unsigned long long)v, 10, 0);
                break;
            }
            case 'u': {
                unsigned long long v = is_llong ? va_arg(ap, unsigned long long) :
                                       is_long  ? va_arg(ap, unsigned long) :
                                                  va_arg(ap, unsigned int);
                len = fmt_uint(buf, v, 10, 0);
                break;
            }
            case 'x': case 'X': {
                unsigned long long v = is_llong ? va_arg(ap, unsigned long long) :
                                       is_long  ? va_arg(ap, unsigned long) :
                                                  va_arg(ap, unsigned int);
                len = fmt_uint(buf, v, 16, *fmt == 'X');
                break;
            }
            case 'o': {
                unsigned long long v = is_llong ? va_arg(ap, unsigned long long) :
                                       is_long  ? va_arg(ap, unsigned long) :
                                                  va_arg(ap, unsigned int);
                len = fmt_uint(buf, v, 8, 0);
                break;
            }
            case 'p': {
                void *p = va_arg(ap, void *);
                sink(ctx, "0x", 2);
                len = fmt_uint(buf, (unsigned long long)(unsigned long)p, 16, 0);
                break;
            }
            case 'c': {
                buf[0] = (char)va_arg(ap, int);
                len = 1;
                break;
            }
            case 's': {
                str = va_arg(ap, const char *);
                if (!str) str = "(null)";
                while (str[slen]) slen++;
                break;
            }
            default:
                sink(ctx, "%", 1);
                if (*fmt) { sink(ctx, fmt, 1); fmt++; }
                continue;
        }
        fmt++;

        if (str) {
            int p = width > slen ? width - slen : 0;
            if (!flag_left) pad(sink, ctx, ' ', p);
            sink(ctx, str, (size_t)slen);
            if (flag_left) pad(sink, ctx, ' ', p);
        } else {
            int total = len + (neg ? 1 : 0);
            int p = width > total ? width - total : 0;
            if (flag_left) {
                if (neg) sink(ctx, "-", 1);
                sink(ctx, buf, (size_t)len);
                pad(sink, ctx, ' ', p);
            } else {
                char padc = flag_zero ? '0' : ' ';
                if (neg) { sink(ctx, "-", 1); pad(sink, ctx, padc, p); }
                else     { pad(sink, ctx, padc, p); }
                sink(ctx, buf, (size_t)len);
            }
        }
    }
}
