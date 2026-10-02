#ifndef _FLIBC_SIGNAL_H
#define _FLIBC_SIGNAL_H

#include <sys/types.h>

typedef int sig_atomic_t;

typedef struct {
    unsigned long __bits[2];
} sigset_t;

typedef void (*sighandler_t)(int);

struct sigaction {
    sighandler_t sa_handler;
    sigset_t sa_mask;
    int sa_flags;
    void (*sa_restorer)(void);
};

#define SIGHUP    1
#define SIGINT    2
#define SIGQUIT   3
#define SIGILL    4
#define SIGTRAP   5
#define SIGABRT   6
#define SIGBUS    7
#define SIGFPE    8
#define SIGKILL   9
#define SIGUSR1   10
#define SIGSEGV   11
#define SIGUSR2   12
#define SIGPIPE   13
#define SIGALRM   14
#define SIGTERM   15
#define SIGCHLD   17
#define SIGCONT   18
#define SIGSTOP   19
#define SIGTSTP   20
#define SIGTTIN   21
#define SIGTTOU   22

#define SIG_DFL ((sighandler_t)0)
#define SIG_IGN ((sighandler_t)1)
#define SIG_ERR ((sighandler_t)-1)

#define SA_RESTORER 0x04000000
#define SA_RESTART  0x10000000

int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);
sighandler_t signal(int signum, sighandler_t handler);
int sigprocmask(int how, const sigset_t *set, sigset_t *oldset);
int sigemptyset(sigset_t *set);
int sigfillset(sigset_t *set);
int sigaddset(sigset_t *set, int signum);
int sigdelset(sigset_t *set, int signum);
int sigismember(const sigset_t *set, int signum);
int kill(pid_t pid, int sig);
int raise(int sig);

#define SIG_BLOCK   0
#define SIG_UNBLOCK 1
#define SIG_SETMASK 2

#endif
