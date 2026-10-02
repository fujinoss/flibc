#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define BUFSZ 4096

struct __flibc_FILE {
    int fd;
    int eof;
    int err;
    int owns_fd;
    int wbuf;
    size_t rpos;
    size_t rlen;
    unsigned char buf[BUFSZ];
};

static struct __flibc_FILE __stdin  = { 0, 0, 0, 0, 0, 0, 0, {0} };
static struct __flibc_FILE __stdout = { 1, 0, 0, 0, 1, 0, 0, {0} };
static struct __flibc_FILE __stderr = { 2, 0, 0, 0, 1, 0, 0, {0} };

FILE *stdin  = &__stdin;
FILE *stdout = &__stdout;
FILE *stderr = &__stderr;

FILE *fopen(const char *path, const char *mode) {
    int flags = O_RDONLY;
    int w = 0;
    if (mode[0] == 'w') { flags = O_WRONLY | O_CREAT | O_TRUNC; w = 1; }
    else if (mode[0] == 'a') { flags = O_WRONLY | O_CREAT | O_APPEND; w = 1; }
    else if (mode[0] == 'r' && mode[1] == '+') { flags = O_RDWR; w = 1; }
    else if (mode[0] == 'w' && mode[1] == '+') { flags = O_RDWR | O_CREAT | O_TRUNC; w = 1; }
    else if (mode[0] == 'a' && mode[1] == '+') { flags = O_RDWR | O_CREAT | O_APPEND; w = 1; }

    int fd = open(path, flags, 0644);
    if (fd < 0) return 0;

    FILE *f = malloc(sizeof *f);
    if (!f) { close(fd); return 0; }
    memset(f, 0, sizeof *f);
    f->fd = fd;
    f->owns_fd = 1;
    f->wbuf = w;
    return f;
}

int fflush(FILE *f) {
    if (!f) return 0;
    if (f->wbuf && f->rpos > 0) {
        ssize_t w = write(f->fd, f->buf, f->rpos);
        if (w < 0) { f->err = 1; return -1; }
        f->rpos = 0;
    }
    return 0;
}

int fclose(FILE *f) {
    if (!f) return -1;
    fflush(f);
    if (f->owns_fd) close(f->fd);
    if (f != stdin && f != stdout && f != stderr) free(f);
    return 0;
}

size_t fwrite(const void *ptr, size_t size, size_t n, FILE *f) {
    size_t total = size * n;
    if (total == 0) return 0;
    if (f->wbuf) {
        const unsigned char *p = ptr;
        size_t done = 0;
        while (done < total) {
            size_t space = BUFSZ - f->rpos;
            size_t take = total - done < space ? total - done : space;
            memcpy(f->buf + f->rpos, p + done, take);
            f->rpos += take;
            done += take;
            if (f->rpos == BUFSZ) fflush(f);
        }
        fflush(f);
    } else {
        ssize_t w = write(f->fd, ptr, total);
        if (w < 0) { f->err = 1; return 0; }
    }
    return n;
}

static int refill(FILE *f) {
    if (f->rpos < f->rlen) return 0;
    ssize_t r = read(f->fd, f->buf, BUFSZ);
    if (r < 0) { f->err = 1; return -1; }
    if (r == 0) { f->eof = 1; return -1; }
    f->rpos = 0;
    f->rlen = (size_t)r;
    return 0;
}

size_t fread(void *ptr, size_t size, size_t n, FILE *f) {
    size_t total = size * n;
    size_t done = 0;
    unsigned char *p = ptr;
    while (done < total) {
        if (refill(f) < 0) break;
        size_t avail = f->rlen - f->rpos;
        size_t take = total - done < avail ? total - done : avail;
        memcpy(p + done, f->buf + f->rpos, take);
        f->rpos += take;
        done += take;
    }
    return done / size;
}

int fgetc(FILE *f) {
    if (refill(f) < 0) return EOF;
    return f->buf[f->rpos++];
}

int fputc(int c, FILE *f) {
    unsigned char b = (unsigned char)c;
    if (f->wbuf) {
        f->buf[f->rpos++] = b;
        if (f->rpos == BUFSZ) fflush(f);
    } else {
        if (write(f->fd, &b, 1) < 0) { f->err = 1; return EOF; }
    }
    return (int)b;
}

char *fgets(char *s, int n, FILE *f) {
    int i = 0;
    if (n <= 0) return 0;
    while (i < n - 1) {
        int c = fgetc(f);
        if (c == EOF) break;
        s[i++] = (char)c;
        if (c == '\n') break;
    }
    s[i] = 0;
    return i > 0 ? s : 0;
}

int feof(FILE *f)   { return f->eof; }
int ferror(FILE *f) { return f->err; }
