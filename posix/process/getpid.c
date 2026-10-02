#include <unistd.h>

extern long __flibc_syscall0(unsigned long n);

#define __NR_getpid  172
#define __NR_getppid 173
#define __NR_getuid  174
#define __NR_geteuid 175
#define __NR_getgid  176
#define __NR_getegid 177

pid_t getpid(void)  { return (pid_t)__flibc_syscall0(__NR_getpid); }
pid_t getppid(void) { return (pid_t)__flibc_syscall0(__NR_getppid); }
uid_t getuid(void)  { return (uid_t)__flibc_syscall0(__NR_getuid); }
uid_t geteuid(void) { return (uid_t)__flibc_syscall0(__NR_geteuid); }
gid_t getgid(void)  { return (gid_t)__flibc_syscall0(__NR_getgid); }
gid_t getegid(void) { return (gid_t)__flibc_syscall0(__NR_getegid); }
