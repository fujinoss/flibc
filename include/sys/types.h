/* flibc — include/sys/types.h
 *
 * Original work. Author: flibc contributors. License: MIT (see LICENSE).
 *
 * POSIX base types. 64-bit only for now; 32-bit ABIs will get
 * their own variants when arm and i686 land.
 */

#ifndef _FLIBC_SYS_TYPES_H
#define _FLIBC_SYS_TYPES_H

typedef unsigned long  size_t;
typedef long           ssize_t;
typedef long           off_t;
typedef int            pid_t;
typedef unsigned int   uid_t;
typedef unsigned int   gid_t;
typedef unsigned int   mode_t;
typedef long           time_t;
typedef long           suseconds_t;

#endif
