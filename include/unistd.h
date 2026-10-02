/* flibc — include/unistd.h
 *
 * Original work. Author: flibc contributors. License: MIT (see LICENSE).
 *
 * POSIX operating system API. Only the functions flibc currently
 * implements are declared here. More are added as they are written.
 */

#ifndef _FLIBC_UNISTD_H
#define _FLIBC_UNISTD_H

#include <sys/types.h>

ssize_t write(int fd, const void *buf, size_t count);
ssize_t read(int fd, void *buf, size_t count);
int     close(int fd);
pid_t   getpid(void);
uid_t   getuid(void);
gid_t   getgid(void);
int     chdir(const char *path);
char   *getcwd(char *buf, size_t size);

#define STDIN_FILENO  0
#define STDOUT_FILENO 1
#define STDERR_FILENO 2

#endif
