#include <string.h>

void *memset(void *dst, int c, size_t n) {
    unsigned char *d = dst;
    unsigned char b = (unsigned char)c;

    while (n && ((unsigned long)d & 7)) {
        *d++ = b;
        n--;
    }

    if (n >= 8) {
        unsigned long w = 0x0101010101010101UL * b;
        unsigned long *dw = (unsigned long *)d;
        while (n >= 8) {
            *dw++ = w;
            n -= 8;
        }
        d = (unsigned char *)dw;
    }

    while (n--) *d++ = b;
    return dst;
}
