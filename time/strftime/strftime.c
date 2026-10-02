#include <time.h>

static void put_pad(char *s, size_t max, size_t *pos, int v, int width, char pad) {
    char tmp[16];
    int n = 0;
    if (v == 0) tmp[n++] = '0';
    while (v > 0) { tmp[n++] = '0' + (v % 10); v /= 10; }
    while (n < width) tmp[n++] = pad;
    while (n > 0 && *pos < max - 1) s[(*pos)++] = tmp[--n];
}

size_t strftime(char *s, size_t max, const char *fmt, const struct tm *tm) {
    size_t pos = 0;
    if (max == 0) return 0;

    while (*fmt && pos < max - 1) {
        if (*fmt != '%') { s[pos++] = *fmt++; continue; }
        fmt++;
        switch (*fmt) {
            case 'Y': put_pad(s, max, &pos, tm->tm_year + 1900, 4, '0'); break;
            case 'm': put_pad(s, max, &pos, tm->tm_mon + 1, 2, '0'); break;
            case 'd': put_pad(s, max, &pos, tm->tm_mday, 2, '0'); break;
            case 'H': put_pad(s, max, &pos, tm->tm_hour, 2, '0'); break;
            case 'M': put_pad(s, max, &pos, tm->tm_min, 2, '0'); break;
            case 'S': put_pad(s, max, &pos, tm->tm_sec, 2, '0'); break;
            case 'j': put_pad(s, max, &pos, tm->tm_yday + 1, 3, '0'); break;
            case '%': if (pos < max - 1) s[pos++] = '%'; break;
            default:  if (pos < max - 1) s[pos++] = *fmt; break;
        }
        fmt++;
    }
    s[pos] = 0;
    return pos;
}
