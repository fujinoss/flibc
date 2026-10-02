#include <signal.h>

int sigemptyset(sigset_t *set) {
    set->__bits[0] = 0;
    set->__bits[1] = 0;
    return 0;
}

int sigfillset(sigset_t *set) {
    set->__bits[0] = ~0UL;
    set->__bits[1] = ~0UL;
    return 0;
}

int sigaddset(sigset_t *set, int signum) {
    if (signum < 1 || signum > 64) return -1;
    int idx = (signum - 1) / 64;
    int bit = (signum - 1) % 64;
    set->__bits[idx] |= (1UL << bit);
    return 0;
}

int sigdelset(sigset_t *set, int signum) {
    if (signum < 1 || signum > 64) return -1;
    int idx = (signum - 1) / 64;
    int bit = (signum - 1) % 64;
    set->__bits[idx] &= ~(1UL << bit);
    return 0;
}

int sigismember(const sigset_t *set, int signum) {
    if (signum < 1 || signum > 64) return -1;
    int idx = (signum - 1) / 64;
    int bit = (signum - 1) % 64;
    return (set->__bits[idx] >> bit) & 1;
}
