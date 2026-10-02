/* flibc — string/mem/memcpy.c
 *
 * Original work. Author: flibc contributors. License: MIT (see LICENSE).
 *
 * memcpy — copy n bytes from src to dst. Regions must not overlap;
 * use memmove for that. Word-at-a-time for aligned regions, byte
 * loop for the head and tail.
 */

#include <string.h>

void *memcpy(void *dst, const void *src, size_t n) {
    unsigned char *d = dst;
    const unsigned char *s = src;

    if (n >= 8 && ((unsigned long)d & 7) == ((unsigned long)s & 7)) {
        while (((unsigned long)d & 7) && n) {
            *d++ = *s++;
            n--;
        }
        unsigned long *dw = (unsigned long *)d;
        const unsigned long *sw = (const unsigned long *)s;
        while (n >= 8) {
            *dw++ = *sw++;
            n -= 8;
        }
        d = (unsigned char *)dw;
        s = (const unsigned char *)sw;
    }

    while (n--) {
        *d++ = *s++;
    }

    return dst;
}
