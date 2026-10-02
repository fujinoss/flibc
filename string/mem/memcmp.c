#include <string.h>

int memcmp(const void *a, const void *b, size_t n) {
    const unsigned char *x = a;
    const unsigned char *y = b;
    while (n--) {
        if (*x != *y) return (int)*x - (int)*y;
        x++; y++;
    }
    return 0;
}
