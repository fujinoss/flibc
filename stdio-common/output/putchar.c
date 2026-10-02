#include <stdio.h>

int fputc(int c, FILE *f);

int putchar(int c) {
    return fputc(c, stdout);
}
