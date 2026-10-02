/* flibc — misc/stack_chk.c
 *
 * Original work. Author: flibc contributors. License: MIT (see LICENSE).
 *
 * __stack_chk_fail is called by code compiled with -fstack-protector
 * when a stack canary is corrupted. It never returns. In a freestanding
 * libc we trap. When we eventually support stack protection properly,
 * this will print a message and abort via SIGABRT.
 */

void __stack_chk_fail(void) {
    __builtin_trap();
}
