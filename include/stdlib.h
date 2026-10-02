#ifndef _FLIBC_STDLIB_H
#define _FLIBC_STDLIB_H

#include <sys/types.h>

void exit(int code) __attribute__((noreturn));
void _exit(int code) __attribute__((noreturn));
void abort(void) __attribute__((noreturn));

void *malloc(size_t size);
void *calloc(size_t n, size_t size);
void *realloc(void *p, size_t size);
void  free(void *p);

#endif
