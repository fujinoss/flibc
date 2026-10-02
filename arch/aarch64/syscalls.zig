//! flibc — arch/aarch64/syscalls.zig
//!
//! Original work. Author: flibc contributors. License: MIT (see LICENSE).
//!
//! Raw Linux syscalls for aarch64 (ARM64). Every flibc function that needs
//! the kernel calls through one of these. No Bionic, no glibc.
//!
//! Syscall numbers come from asm-generic/unistd.h. aarch64 uses svc #0.
//! Kernel convention: return in x0; negative values in [-4095, -1] are -errno.

const std = @import("std");

pub const Error = error{
    EPERM, ENOENT, ESRCH, EINTR, EIO, ENXIO, E2BIG, ENOEXEC, EBADF,
    ECHILD, EAGAIN, ENOMEM, EACCES, EFAULT, EBUSY, EEXIST, EXDEV,
    ENODEV, ENOTDIR, EISDIR, EINVAL, ENFILE, EMFILE, ENOTTY, ETXTBSY,
    EFBIG, ENOSPC, ESPIPE, EROFS, EMLINK, EPIPE, EDOM, ERANGE,
    EDEADLK, ENAMETOOLONG, ENOLCK, ENOSYS, ENOTEMPTY, ELOOP,
    EOVERFLOW, EOPNOTSUPP, ETIMEDOUT, EBADMSG, EILSEQ, ENOTSOCK,
    EDESTADDRREQ, EMSGSIZE, EPROTOTYPE, ENOPROTOOPT, EPROTONOSUPPORT,
    EAFNOSUPPORT, EADDRINUSE, EADDRNOTAVAIL, ENETDOWN, ENETUNREACH,
    ECONNABORTED, ECONNRESET, ENOBUFS, EISCONN, ENOTCONN, ESHUTDOWN,
    ETOOMANYREFS, ECONNREFUSED, EHOSTDOWN, EHOSTUNREACH, EALREADY,
    EINPROGRESS, ESTALE, EDQUOT, ECANCELED, EOWNERDEAD, ENOTRECOVERABLE,
    UNKNOWN,
};

pub inline fn isError(ret: isize) bool {
    return ret < 0 and ret > -4096;
}

pub inline fn toError(ret: isize) Error {
    return switch (-ret) {
        1 => error.EPERM, 2 => error.ENOENT, 3 => error.ESRCH,
        4 => error.EINTR, 5 => error.EIO, 6 => error.ENXIO,
        7 => error.E2BIG, 8 => error.ENOEXEC, 9 => error.EBADF,
        10 => error.ECHILD, 11 => error.EAGAIN, 12 => error.ENOMEM,
        13 => error.EACCES, 14 => error.EFAULT, 16 => error.EBUSY,
        17 => error.EEXIST, 18 => error.EXDEV, 19 => error.ENODEV,
        20 => error.ENOTDIR, 21 => error.EISDIR, 22 => error.EINVAL,
        23 => error.ENFILE, 24 => error.EMFILE, 25 => error.ENOTTY,
        26 => error.ETXTBSY, 27 => error.EFBIG, 28 => error.ENOSPC,
        29 => error.ESPIPE, 30 => error.EROFS, 31 => error.EMLINK,
        32 => error.EPIPE, 33 => error.EDOM, 34 => error.ERANGE,
        35 => error.EDEADLK, 36 => error.ENAMETOOLONG, 37 => error.ENOLCK,
        38 => error.ENOSYS, 39 => error.ENOTEMPTY, 40 => error.ELOOP,
        74 => error.EBADMSG, 75 => error.EOVERFLOW, 84 => error.EILSEQ,
        88 => error.ENOTSOCK, 89 => error.EDESTADDRREQ, 90 => error.EMSGSIZE,
        91 => error.EPROTOTYPE, 92 => error.ENOPROTOOPT,
        93 => error.EPROTONOSUPPORT, 95 => error.EOPNOTSUPP,
        97 => error.EAFNOSUPPORT, 98 => error.EADDRINUSE,
        99 => error.EADDRNOTAVAIL, 100 => error.ENETDOWN,
        101 => error.ENETUNREACH, 103 => error.ECONNABORTED,
        104 => error.ECONNRESET, 105 => error.ENOBUFS, 106 => error.EISCONN,
        107 => error.ENOTCONN, 108 => error.ESHUTDOWN,
        109 => error.ETOOMANYREFS, 110 => error.ETIMEDOUT,
        111 => error.ECONNREFUSED, 112 => error.EHOSTDOWN,
        113 => error.EHOSTUNREACH, 114 => error.EALREADY,
        115 => error.EINPROGRESS, 116 => error.ESTALE, 122 => error.EDQUOT,
        125 => error.ECANCELED, 130 => error.EOWNERDEAD,
        131 => error.ENOTRECOVERABLE,
        else => error.UNKNOWN,
    };
}

pub const SYS = struct {
    pub const io_setup = 0;
    pub const io_destroy = 1;
    pub const io_submit = 2;
    pub const io_cancel = 3;
    pub const io_getevents = 4;
    pub const setxattr = 5;
    pub const lsetxattr = 6;
    pub const fsetxattr = 7;
    pub const getxattr = 8;
    pub const lgetxattr = 9;
    pub const fgetxattr = 10;
    pub const listxattr = 11;
    pub const llistxattr = 12;
    pub const flistxattr = 13;
    pub const removexattr = 14;
    pub const lremovexattr = 15;
    pub const fremovexattr = 16;
    pub const getcwd = 17;
    pub const lookup_dcookie = 18;
    pub const eventfd2 = 19;
    pub const epoll_create1 = 20;
    pub const epoll_ctl = 21;
    pub const epoll_pwait = 22;
    pub const dup = 23;
    pub const dup3 = 24;
    pub const fcntl = 25;
    pub const inotify_init1 = 26;
    pub const inotify_add_watch = 27;
    pub const inotify_rm_watch = 28;
    pub const ioctl = 29;
    pub const ioprio_set = 30;
    pub const ioprio_get = 31;
    pub const flock = 32;
    pub const mknodat = 33;
    pub const mkdirat = 34;
    pub const unlinkat = 35;
    pub const symlinkat = 36;
    pub const linkat = 37;
    pub const renameat = 38;
    pub const umount2 = 39;
    pub const mount = 40;
    pub const pivot_root = 41;
    pub const statfs = 43;
    pub const fstatfs = 44;
    pub const truncate = 45;
    pub const ftruncate = 46;
    pub const fallocate = 47;
    pub const faccessat = 48;
    pub const chdir = 49;
    pub const fchdir = 50;
    pub const chroot = 51;
    pub const fchmod = 52;
    pub const fchmodat = 53;
    pub const fchownat = 54;
    pub const fchown = 55;
    pub const openat = 56;
    pub const close = 57;
    pub const vhangup = 58;
    pub const pipe2 = 59;
    pub const quotactl = 60;
    pub const getdents64 = 61;
    pub const lseek = 62;
    pub const read = 63;
    pub const write = 64;
    pub const readv = 65;
    pub const writev = 66;
    pub const pread64 = 67;
    pub const pwrite64 = 68;
    pub const preadv = 69;
    pub const pwritev = 70;
    pub const sendfile = 71;
    pub const pselect6 = 72;
    pub const ppoll = 73;
    pub const signalfd4 = 74;
    pub const vmsplice = 75;
    pub const splice = 76;
    pub const tee = 77;
    pub const readlinkat = 78;
    pub const newfstatat = 79;
    pub const fstat = 80;
    pub const sync = 81;
    pub const fsync = 82;
    pub const fdatasync = 83;
    pub const sync_file_range = 84;
    pub const timerfd_create = 85;
    pub const timerfd_settime = 86;
    pub const timerfd_gettime = 87;
    pub const utimensat = 88;
    pub const acct = 89;
    pub const capget = 90;
    pub const capset = 91;
    pub const personality = 92;
    pub const exit = 93;
    pub const exit_group = 94;
    pub const waitid = 95;
    pub const set_tid_address = 96;
    pub const unshare = 97;
    pub const futex = 98;
    pub const set_robust_list = 99;
    pub const get_robust_list = 100;
    pub const nanosleep = 101;
    pub const getitimer = 102;
    pub const setitimer = 103;
    pub const kexec_load = 104;
    pub const init_module = 105;
    pub const delete_module = 106;
    pub const timer_create = 107;
    pub const timer_gettime = 108;
    pub const timer_getoverrun = 109;
    pub const timer_settime = 110;
    pub const timer_delete = 111;
    pub const clock_settime = 112;
    pub const clock_gettime = 113;
    pub const clock_getres = 114;
    pub const clock_nanosleep = 115;
    pub const syslog = 116;
    pub const ptrace = 117;
    pub const sched_setparam = 118;
    pub const sched_setscheduler = 119;
    pub const sched_getscheduler = 120;
    pub const sched_getparam = 121;
    pub const sched_setaffinity = 122;
    pub const sched_getaffinity = 123;
    pub const sched_yield = 124;
    pub const sched_get_priority_max = 125;
    pub const sched_get_priority_min = 126;
    pub const sched_rr_get_interval = 127;
    pub const restart_syscall = 128;
    pub const kill = 129;
    pub const tkill = 130;
    pub const tgkill = 131;
    pub const sigaltstack = 132;
    pub const rt_sigsuspend = 133;
    pub const rt_sigaction = 134;
    pub const rt_sigprocmask = 135;
    pub const rt_sigpending = 136;
    pub const rt_sigtimedwait = 137;
    pub const rt_sigqueueinfo = 138;
    pub const rt_sigreturn = 139;
    pub const setpriority = 140;
    pub const getpriority = 141;
    pub const reboot = 142;
    pub const setregid = 143;
    pub const setgid = 144;
    pub const setreuid = 145;
    pub const setuid = 146;
    pub const setresuid = 147;
    pub const getresuid = 148;
    pub const setresgid = 149;
    pub const getresgid = 150;
    pub const setfsuid = 151;
    pub const setfsgid = 152;
    pub const times = 153;
    pub const setpgid = 154;
    pub const getpgid = 155;
    pub const getsid = 156;
    pub const setsid = 157;
    pub const getgroups = 158;
    pub const setgroups = 159;
    pub const uname = 160;
    pub const sethostname = 161;
    pub const setdomainname = 162;
    pub const getrlimit = 163;
    pub const setrlimit = 164;
    pub const getrusage = 165;
    pub const umask = 166;
    pub const prctl = 167;
    pub const getcpu = 168;
    pub const gettimeofday = 169;
    pub const settimeofday = 170;
    pub const adjtimex = 171;
    pub const getpid = 172;
    pub const getppid = 173;
    pub const getuid = 174;
    pub const geteuid = 175;
    pub const getgid = 176;
    pub const getegid = 177;
    pub const gettid = 178;
    pub const sysinfo = 179;
    pub const mq_open = 180;
    pub const mq_unlink = 181;
    pub const mq_timedsend = 182;
    pub const mq_timedreceive = 183;
    pub const mq_notify = 184;
    pub const mq_getsetattr = 185;
    pub const msgget = 186;
    pub const msgctl = 187;
    pub const msgrcv = 188;
    pub const msgsnd = 189;
    pub const semget = 190;
    pub const semctl = 191;
    pub const semtimedop = 192;
    pub const semop = 193;
    pub const shmget = 194;
    pub const shmctl = 195;
    pub const shmat = 196;
    pub const shmdt = 197;
    pub const socket = 198;
    pub const socketpair = 199;
    pub const bind = 200;
    pub const listen = 201;
    pub const accept = 202;
    pub const connect = 203;
    pub const getsockname = 204;
    pub const getpeername = 205;
    pub const sendto = 206;
    pub const recvfrom = 207;
    pub const setsockopt = 208;
    pub const getsockopt = 209;
    pub const shutdown = 210;
    pub const sendmsg = 211;
    pub const recvmsg = 212;
    pub const readahead = 213;
    pub const brk = 214;
    pub const munmap = 215;
    pub const mremap = 216;
    pub const add_key = 217;
    pub const request_key = 218;
    pub const keyctl = 219;
    pub const clone = 220;
    pub const execve = 221;
    pub const mmap = 222;
    pub const fadvise64 = 223;
    pub const swapon = 224;
    pub const swapoff = 225;
    pub const mprotect = 226;
    pub const msync = 227;
    pub const mlock = 228;
    pub const munlock = 229;
    pub const mlockall = 230;
    pub const munlockall = 231;
    pub const mincore = 232;
    pub const madvise = 233;
    pub const remap_file_pages = 234;
    pub const mbind = 235;
    pub const get_mempolicy = 236;
    pub const set_mempolicy = 237;
    pub const migrate_pages = 238;
    pub const move_pages = 239;
    pub const rt_tgsigqueueinfo = 240;
    pub const perf_event_open = 241;
    pub const accept4 = 242;
    pub const recvmmsg = 243;
    pub const wait4 = 260;
    pub const prlimit64 = 261;
    pub const fanotify_init = 262;
    pub const fanotify_mark = 263;
    pub const name_to_handle_at = 264;
    pub const open_by_handle_at = 265;
    pub const clock_adjtime = 266;
    pub const syncfs = 267;
    pub const setns = 268;
    pub const sendmmsg = 269;
    pub const process_vm_readv = 270;
    pub const process_vm_writev = 271;
    pub const kcmp = 272;
    pub const finit_module = 273;
    pub const sched_setattr = 274;
    pub const sched_getattr = 275;
    pub const renameat2 = 276;
    pub const seccomp = 277;
    pub const getrandom = 278;
    pub const memfd_create = 279;
    pub const bpf = 280;
    pub const execveat = 281;
    pub const userfaultfd = 282;
    pub const membarrier = 283;
    pub const mlock2 = 284;
    pub const copy_file_range = 285;
    pub const preadv2 = 286;
    pub const pwritev2 = 287;
    pub const pkey_mprotect = 288;
    pub const pkey_alloc = 289;
    pub const pkey_free = 290;
    pub const statx = 291;
    pub const io_pgetevents = 292;
    pub const rseq = 293;
    pub const kexec_file_load = 294;
    pub const pidfd_send_signal = 424;
    pub const io_uring_setup = 425;
    pub const io_uring_enter = 426;
    pub const io_uring_register = 427;
    pub const open_tree = 428;
    pub const move_mount = 429;
    pub const fsopen = 430;
    pub const fsconfig = 431;
    pub const fsmount = 432;
    pub const fspick = 433;
    pub const pidfd_open = 434;
    pub const clone3 = 435;
    pub const close_range = 436;
    pub const openat2 = 437;
    pub const pidfd_getfd = 438;
    pub const faccessat2 = 439;
    pub const process_madvise = 440;
    pub const epoll_pwait2 = 441;
    pub const mount_setattr = 442;
    pub const quotactl_fd = 443;
    pub const landlock_create_ruleset = 444;
    pub const landlock_add_rule = 445;
    pub const landlock_restrict_self = 446;
    pub const memfd_secret = 447;
    pub const process_mrelease = 448;
    pub const futex_waitv = 449;
    pub const set_mempolicy_home_node = 450;
};

pub inline fn syscall0(n: usize) isize {
    return asm volatile ("svc #0"
        : [ret] "={x0}" (-> isize),
        : [n] "{x8}" (n),
        : .{ .memory = true }
    );
}

pub inline fn syscall1(n: usize, a1: usize) isize {
    return asm volatile ("svc #0"
        : [ret] "={x0}" (-> isize),
        : [n] "{x8}" (n),
          [a1] "{x0}" (a1),
        : .{ .memory = true }
    );
}

pub inline fn syscall2(n: usize, a1: usize, a2: usize) isize {
    return asm volatile ("svc #0"
        : [ret] "={x0}" (-> isize),
        : [n] "{x8}" (n),
          [a1] "{x0}" (a1),
          [a2] "{x1}" (a2),
        : .{ .memory = true }
    );
}

pub inline fn syscall3(n: usize, a1: usize, a2: usize, a3: usize) isize {
    return asm volatile ("svc #0"
        : [ret] "={x0}" (-> isize),
        : [n] "{x8}" (n),
          [a1] "{x0}" (a1),
          [a2] "{x1}" (a2),
          [a3] "{x2}" (a3),
        : .{ .memory = true }
    );
}

pub inline fn syscall4(n: usize, a1: usize, a2: usize, a3: usize, a4: usize) isize {
    return asm volatile ("svc #0"
        : [ret] "={x0}" (-> isize),
        : [n] "{x8}" (n),
          [a1] "{x0}" (a1),
          [a2] "{x1}" (a2),
          [a3] "{x2}" (a3),
          [a4] "{x3}" (a4),
        : .{ .memory = true }
    );
}

pub inline fn syscall5(n: usize, a1: usize, a2: usize, a3: usize, a4: usize, a5: usize) isize {
    return asm volatile ("svc #0"
        : [ret] "={x0}" (-> isize),
        : [n] "{x8}" (n),
          [a1] "{x0}" (a1),
          [a2] "{x1}" (a2),
          [a3] "{x2}" (a3),
          [a4] "{x3}" (a4),
          [a5] "{x4}" (a5),
        : .{ .memory = true }
    );
}

pub inline fn syscall6(n: usize, a1: usize, a2: usize, a3: usize, a4: usize, a5: usize, a6: usize) isize {
    return asm volatile ("svc #0"
        : [ret] "={x0}" (-> isize),
        : [n] "{x8}" (n),
          [a1] "{x0}" (a1),
          [a2] "{x1}" (a2),
          [a3] "{x2}" (a3),
          [a4] "{x3}" (a4),
          [a5] "{x4}" (a5),
          [a6] "{x5}" (a6),
        : .{ .memory = true }
    );
}

pub fn read(fd: i32, buf: []u8) Error!usize {
    const ret = syscall3(SYS.read, @intCast(fd), @intFromPtr(buf.ptr), buf.len);
    if (isError(ret)) return toError(ret);
    return @intCast(ret);
}

pub fn write(fd: i32, buf: []const u8) Error!usize {
    const ret = syscall3(SYS.write, @intCast(fd), @intFromPtr(buf.ptr), buf.len);
    if (isError(ret)) return toError(ret);
    return @intCast(ret);
}

pub fn openat(dirfd: i32, path: [*:0]const u8, flags: u32, mode: u32) Error!i32 {
    const ret = syscall4(SYS.openat, @bitCast(@as(isize, dirfd)), @intFromPtr(path), flags, mode);
    if (isError(ret)) return toError(ret);
    return @intCast(ret);
}

pub fn close(fd: i32) Error!void {
    const ret = syscall1(SYS.close, @intCast(fd));
    if (isError(ret)) return toError(ret);
}

pub fn exit(code: u8) noreturn {
    _ = syscall1(SYS.exit_group, @intCast(code));
    unreachable;
}

pub fn getpid() i32 {
    const ret = syscall0(SYS.getpid);
    return @intCast(ret);
}

pub fn getuid() u32 {
    const ret = syscall0(SYS.getuid);
    return @intCast(ret);
}

pub fn getgid() u32 {
    const ret = syscall0(SYS.getgid);
    return @intCast(ret);
}

pub fn getcwd(buf: []u8) Error![]u8 {
    const ret = syscall2(SYS.getcwd, @intFromPtr(buf.ptr), buf.len);
    if (isError(ret)) return toError(ret);
    return buf[0..@intCast(ret)];
}

pub fn chdir(path: [*:0]const u8) Error!void {
    const ret = syscall1(SYS.chdir, @intFromPtr(path));
    if (isError(ret)) return toError(ret);
}

pub fn mkdirat(dirfd: i32, path: [*:0]const u8, mode: u32) Error!void {
    const ret = syscall3(SYS.mkdirat, @bitCast(@as(isize, dirfd)), @intFromPtr(path), mode);
    if (isError(ret)) return toError(ret);
}

pub fn unlinkat(dirfd: i32, path: [*:0]const u8, flags: u32) Error!void {
    const ret = syscall3(SYS.unlinkat, @bitCast(@as(isize, dirfd)), @intFromPtr(path), flags);
    if (isError(ret)) return toError(ret);
}

pub fn nanosleep(req: *const timespec, rem: ?*timespec) Error!void {
    const rem_ptr = if (rem) |r| @intFromPtr(r) else 0;
    const ret = syscall2(SYS.nanosleep, @intFromPtr(req), rem_ptr);
    if (isError(ret)) return toError(ret);
}

pub const timespec = extern struct {
    sec: i64,
    nsec: i64,
};

pub fn clock_gettime(clock_id: u32, tp: *timespec) Error!void {
    const ret = syscall2(SYS.clock_gettime, clock_id, @intFromPtr(tp));
    if (isError(ret)) return toError(ret);
}

pub const CLOCK_REALTIME: u32 = 0;
pub const CLOCK_MONOTONIC: u32 = 1;

pub const AT_FDCWD: i32 = -100;

pub const O_RDONLY: u32 = 0o0;
pub const O_WRONLY: u32 = 0o1;
pub const O_RDWR: u32 = 0o2;
pub const O_CREAT: u32 = 0o100;
pub const O_EXCL: u32 = 0o200;
pub const O_TRUNC: u32 = 0o1000;
pub const O_APPEND: u32 = 0o2000;

test "write hello to stdout" {
    const written = try write(1, "hello from flibc syscalls\n");
    try std.testing.expect(written > 0);
}

test "getpid returns positive" {
    const pid = getpid();
    try std.testing.expect(pid > 0);
}

test "getuid and getgid" {
    const uid = getuid();
    const gid = getgid();
    try std.testing.expect(uid >= 0);
    try std.testing.expect(gid >= 0);
}

test "open nonexistent file returns ENOENT" {
    const ret = openat(AT_FDCWD, "/this/does/not/exist", O_RDONLY, 0);
    try std.testing.expectError(error.ENOENT, ret);
}

test "clock_gettime monotonic" {
    var ts: timespec = undefined;
    try clock_gettime(CLOCK_MONOTONIC, &ts);
    try std.testing.expect(ts.sec > 0);
}

export fn __flibc_syscall0(n: usize) isize {
    return syscall0(n);
}

export fn __flibc_syscall1(n: usize, a1: usize) isize {
    return syscall1(n, a1);
}

export fn __flibc_syscall2(n: usize, a1: usize, a2: usize) isize {
    return syscall2(n, a1, a2);
}

export fn __flibc_syscall3(n: usize, a1: usize, a2: usize, a3: usize) isize {
    return syscall3(n, a1, a2, a3);
}

export fn __flibc_syscall4(n: usize, a1: usize, a2: usize, a3: usize, a4: usize) isize {
    return syscall4(n, a1, a2, a3, a4);
}

export fn __flibc_syscall5(n: usize, a1: usize, a2: usize, a3: usize, a4: usize, a5: usize) isize {
    return syscall5(n, a1, a2, a3, a4, a5);
}

export fn __flibc_syscall6(n: usize, a1: usize, a2: usize, a3: usize, a4: usize, a5: usize, a6: usize) isize {
    return syscall6(n, a1, a2, a3, a4, a5, a6);
}
