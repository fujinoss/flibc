#include <time.h>

static struct tm shared;

static const int days_in_month[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

static int is_leap(int y) {
    return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
}

struct tm *gmtime_r(const time_t *t, struct tm *out) {
    long secs = (long)*t;
    long days = secs / 86400;
    long rem = secs % 86400;
    if (rem < 0) { rem += 86400; days -= 1; }

    out->tm_hour = (int)(rem / 3600);
    out->tm_min = (int)((rem % 3600) / 60);
    out->tm_sec = (int)(rem % 60);
    out->tm_wday = (int)((days + 4) % 7);
    if (out->tm_wday < 0) out->tm_wday += 7;

    int year = 1970;
    while (1) {
        int ydays = is_leap(year) ? 366 : 365;
        if (days < ydays) break;
        days -= ydays;
        year++;
    }
    out->tm_year = year - 1900;
    out->tm_yday = (int)days;

    int month = 0;
    while (month < 12) {
        int mdays = days_in_month[month];
        if (month == 1 && is_leap(year)) mdays = 29;
        if (days < mdays) break;
        days -= mdays;
        month++;
    }
    out->tm_mon = month;
    out->tm_mday = (int)days + 1;
    out->tm_isdst = 0;
    return out;
}

struct tm *gmtime(const time_t *t) {
    return gmtime_r(t, &shared);
}

struct tm *localtime(const time_t *t) {
    return gmtime(t);
}

time_t mktime(struct tm *tm) {
    long year = tm->tm_year + 1900;
    long days = 0;
    if (year >= 1970) {
        for (long y = 1970; y < year; y++)
            days += is_leap((int)y) ? 366 : 365;
    }
    for (int m = 0; m < tm->tm_mon; m++) {
        days += days_in_month[m];
        if (m == 1 && is_leap((int)year)) days += 1;
    }
    days += tm->tm_mday - 1;
    return (time_t)(days * 86400 + tm->tm_hour * 3600 +
                    tm->tm_min * 60 + tm->tm_sec);
}
