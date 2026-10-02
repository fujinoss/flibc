/* flibc — string/mem/memmove.c
 *
 * Original work. Author: flibc contributors. License: MIT (see LICENSE).
 *
 * memmove — copy n bytes, handling overlapping regions correctly.
 * If dst is before src, copy forward. If dst is after src, copy
 * backward. Otherwise the same as memcpy.
 */

#include <string.h>

void *memmove(void *dst, const void *src, size_t n) {
    unsigned char *d = dst;
    const unsigned char *s = src;

    if (d == s || n == 0) return dst;

    if (d < s) {
        while (n && ((unsigned long)d & 7) && ((unsigned long)s & 7)) {
            *d++ = *s++;
            n--;
        }
        if (n >= 8 && ((unsigned long)d & 7) == ((unsigned long)s & 7)) {
            unsigned long *dw = (unsigned long *)d;
            const unsigned long *sw = (const unsigned long *)s;
            while (n >= 8) {
                *dw++ = *sw++;
                n -= 8;
            }
            d = (unsigned char *)dw;
            s = (const unsigned char *)sw;
        }
        while (n--) *d++ = *s++;
    } else {
        d += n;
        s += n;
        while (n--) *--d = *--s;
    }

    return dst;
}
