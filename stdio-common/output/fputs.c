#include <stdio.h>
#include <string.h>

size_t fwrite(const void *ptr, size_t size, size_t n, FILE *f);

int fputs(const char *s, FILE *f) {
    size_t n = strlen(s);
    fwrite(s, 1, n, f);
    return (int)n;
}
