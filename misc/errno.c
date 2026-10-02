/* flibc — misc/errno.c
 *
 * Original work. Author: flibc contributors. License: MIT (see LICENSE).
 *
 * __errno_location() returns a pointer to the current errno value.
 * Currently a single global. When threads land, this becomes a
 * thread-local via the TLS block.
 */

static int __flibc_errno_storage = 0;

int *__errno_location(void) {
    return &__flibc_errno_storage;
}
