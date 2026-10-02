#ifndef _FLIBC_STDLIB_H
#define _FLIBC_STDLIB_H

#include <sys/types.h>

void exit(int code) __attribute__((noreturn));
void _exit(int code) __attribute__((noreturn));
void abort(void) __attribute__((noreturn));

#endif
