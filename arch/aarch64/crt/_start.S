// flibc — arch/aarch64/crt/_start.S
//
// Original work. Author: flibc contributors. License: MIT (see LICENSE).
//
// Process entry point for aarch64.
//
// The kernel jumps here with the stack laid out as:
//     sp[0] = argc
//     sp[1..argc] = argv[0..argc-1]
//     sp[argc+1] = NULL
//     sp[argc+2..] = envp[0..n-1]
//     ... = NULL
//     ... = auxv (key, value pairs, terminated by AT_NULL)
//
// We pass (argc, argv, envp) to main, then syscall exit_group(ret).
// Also saves the auxv pointer for the dynamic linker / libc to find later.

.global _start
.type _start, %function

_start:
    // On entry: sp points at argc.
    ldr x0, [sp]              // x0 = argc
    add x1, sp, #8            // x1 = &argv[0]

    // envp = &argv[argc + 1]
    add x2, x1, x0, lsl #3    // x2 = argv + argc * 8
    add x2, x2, #8            // x2 = &envp[0]

    // Save envp and argc for __libc_start_main / __flibc_init later.
    adrp x3, __flibc_envp
    add  x3, x3, :lo12:__flibc_envp
    str x2, [x3]

    // Align stack to 16 bytes before calling C.
    mov x9, sp
    and x9, x9, #-16
    mov sp, x9

    // main(argc, argv, envp)
    bl main

    // exit_group(main_return)
    mov x8, #94               // __NR_exit_group
    svc #0

    // Never reached.
    brk #0

.size _start, . - _start

.data
.global __flibc_envp
__flibc_envp:
    .quad 0
