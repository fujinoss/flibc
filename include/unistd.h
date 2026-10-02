#ifndef _FLIBC_UNISTD_H
#define _FLIBC_UNISTD_H

#include <sys/types.h>

ssize_t write(int fd, const void *buf, size_t count);
ssize_t read(int fd, void *buf, size_t count);
off_t   lseek(int fd, off_t offset, int whence);

int     close(int fd);
int     chdir(const char *path);
char   *getcwd(char *buf, size_t size);

pid_t   getpid(void);
pid_t   getppid(void);
uid_t   getuid(void);
uid_t   geteuid(void);
gid_t   getgid(void);
gid_t   getegid(void);
pid_t   fork(void);
int     pipe(int fds[2]);

#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2

#define STDIN_FILENO  0
#define STDOUT_FILENO 1
#define STDERR_FILENO 2

#endif
