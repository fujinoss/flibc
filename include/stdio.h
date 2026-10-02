#ifndef _FLIBC_STDIO_H
#define _FLIBC_STDIO_H

#include <sys/types.h>
#include <stdarg.h>

typedef struct __flibc_FILE FILE;

extern FILE *stdin;
extern FILE *stdout;
extern FILE *stderr;

FILE *fopen(const char *path, const char *mode);
int   fclose(FILE *f);
size_t fread(void *ptr, size_t size, size_t n, FILE *f);
size_t fwrite(const void *ptr, size_t size, size_t n, FILE *f);
int   fgetc(FILE *f);
int   fputc(int c, FILE *f);
char *fgets(char *s, int n, FILE *f);
int   fputs(const char *s, FILE *f);
int   fflush(FILE *f);
int   feof(FILE *f);
int   ferror(FILE *f);

int printf(const char *fmt, ...);
int fprintf(FILE *f, const char *fmt, ...);
int puts(const char *s);
int putchar(int c);
int snprintf(char *buf, size_t n, const char *fmt, ...);
int vsnprintf(char *buf, size_t n, const char *fmt, va_list ap);

#define EOF (-1)

#endif
