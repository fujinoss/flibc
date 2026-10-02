#include <string.h>

#define ONES  0x0101010101010101UL
#define HIGHS 0x8080808080808080UL

static inline int has_zero(unsigned long w) {
    return ((w - ONES) & ~w & HIGHS) != 0;
}

size_t strlen(const char *s) {
    const char *p = s;

    while ((unsigned long)p & 7) {
        if (*p == '\0') return (size_t)(p - s);
        p++;
    }

    const unsigned long *w = (const unsigned long *)p;
    while (!has_zero(*w)) {
        w++;
    }

    p = (const char *)w;
    while (*p != '\0') {
        p++;
    }
    return (size_t)(p - s);
}
