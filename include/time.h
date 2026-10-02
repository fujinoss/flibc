#ifndef _FLIBC_TIME_H
#define _FLIBC_TIME_H

#include <sys/types.h>

struct timespec {
    time_t tv_sec;
    long   tv_nsec;
};

struct tm {
    int tm_sec;
    int tm_min;
    int tm_hour;
    int tm_mday;
    int tm_mon;
    int tm_year;
    int tm_wday;
    int tm_yday;
    int tm_isdst;
};

#define CLOCK_REALTIME           0
#define CLOCK_MONOTONIC          1
#define CLOCK_PROCESS_CPUTIME_ID 2
#define CLOCK_THREAD_CPUTIME_ID  3

int    clock_gettime(int clk, struct timespec *tp);
int    clock_getres(int clk, struct timespec *tp);
time_t time(time_t *t);
int    nanosleep(const struct timespec *req, struct timespec *rem);

struct tm *gmtime(const time_t *t);
struct tm *gmtime_r(const time_t *t, struct tm *out);
struct tm *localtime(const time_t *t);
time_t     mktime(struct tm *tm);

size_t strftime(char *s, size_t max, const char *fmt, const struct tm *tm);

#endif
