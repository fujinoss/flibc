#include <fcntl.h>
#include <stdarg.h>

int openat(int dirfd, const char *path, int flags, ...);

int open(const char *path, int flags, ...) {
    unsigned int mode = 0;
    if (flags & O_CREAT) {
        va_list ap;
        va_start(ap, flags);
        mode = (unsigned int)va_arg(ap, int);
        va_end(ap);
    }
    return openat(AT_FDCWD, path, flags, mode);
}
