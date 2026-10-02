#ifndef _FLIBC_STDIO_H
#define _FLIBC_STDIO_H

#include <sys/types.h>
#include <stdarg.h>

int printf(const char *fmt, ...);
int puts(const char *s);
int fputs(const char *s, void *stream);
int snprintf(char *buf, size_t n, const char *fmt, ...);
int vsnprintf(char *buf, size_t n, const char *fmt, va_list ap);

#endif
