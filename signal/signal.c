#include <signal.h>

int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);

sighandler_t signal(int signum, sighandler_t handler) {
    struct sigaction sa, old;
    sa.sa_handler = handler;
    sa.sa_flags = 0;
    sa.sa_restorer = 0;
    sigemptyset(&sa.sa_mask);

    if (sigaction(signum, &sa, &old) < 0) return SIG_ERR;
    return old.sa_handler;
}
